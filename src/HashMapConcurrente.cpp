#ifndef CHM_CPP
#define CHM_CPP

#include <thread>
#include <iostream>
#include <fstream>

#include "HashMapConcurrente.hpp"

HashMapConcurrente::HashMapConcurrente() {
    _semaforos = std::vector<sem_t>(HashMapConcurrente::cantLetras);
    for (unsigned int i = 0; i < HashMapConcurrente::cantLetras; i++) {
        sem_init(&_semaforos[i], 0, 1);
        tabla[i] = new ListaAtomica<hashMapPair>();
    }
}

unsigned int HashMapConcurrente::hashIndex(std::string clave) {
    return (unsigned int)(std::tolower(clave[0]) - 'a') /*% HashMapConcurrente::cantLetras*/;
}

void HashMapConcurrente::incrementar(std::string clave) {
    // Completar (Ejercicio 2)

    unsigned int index = hashIndex(clave);

    sem_wait(&_semaforos[index]);

    for (auto& p : *tabla[index]) {
        if(p.first == clave){
            p.second = p.second + 1;
            sem_post(&_semaforos[index]);
            return;
        }
    }
    tabla[index]->insertar(hashMapPair(clave, 1));
    sem_post(&_semaforos[index]);
}

std::vector<std::string> HashMapConcurrente::claves() {
    // Completar (Ejercicio 2)

    std::vector<std::string> claves_tabla = std::vector<std::string>();

    for (unsigned int index = 0; index < HashMapConcurrente::cantLetras; index++) {
        sem_wait(&_semaforos[index]);
    }

    for (unsigned int index = 0; index < HashMapConcurrente::cantLetras; index++) {
        for (const auto& p : *tabla[index]) {
            claves_tabla.push_back(p.first);
        }
        sem_post(&_semaforos[index]);
    }
    return claves_tabla;
    
}

unsigned int HashMapConcurrente::valor(std::string clave) {
    // Completar (Ejercicio 2)

    unsigned int index = hashIndex(clave);
        
    sem_wait(&_semaforos[index]);
    for (const auto& p : *tabla[index]) {
        if(p.first == clave){
            sem_post(&_semaforos[index]);
            return p.second;
        }
    }
    sem_post(&_semaforos[index]);

    return 0;
}

float HashMapConcurrente::promedio() {

    float sum = 0.0;
    unsigned int count = 0;

    for (unsigned int index = 0; index < HashMapConcurrente::cantLetras; index++) {
        sem_wait(&_semaforos[index]);
    }

    for (unsigned int index = 0; index < HashMapConcurrente::cantLetras; index++) {
        for (const auto& p : *tabla[index]) {
            sum += p.second;
            count++;
        }
        sem_post(&_semaforos[index]);
    }
    if (count > 0) {
        return sum / count;
    }
    return 0;        
}

void HashMapConcurrente::proceso_thread_promedio(std::atomic<unsigned int> &suma_total, std::atomic<unsigned int> &elementos_total, std::atomic<unsigned int> &lista_actual){
    while (true) {
        unsigned int index = lista_actual.fetch_add(1);
        if (index >= HashMapConcurrente::cantLetras) break;

        unsigned int suma_fila = 0;
        unsigned int elementos_fila = 0;

        sem_wait(&_semaforos[index]);

        for (hashMapPair elemento : *tabla[index]) {
            suma_fila += elemento.second;
            elementos_fila++;
        }

        sem_post(&_semaforos[index]);

        suma_total.fetch_add(suma_fila);
        elementos_total.fetch_add(elementos_fila);
    }
}

float HashMapConcurrente::promedioParalelo(unsigned int cantThreads) {
    std::atomic<unsigned int> suma_total(0);
    std::atomic<unsigned int> elementos_total(0);
    std::atomic<unsigned int> lista_actual(0);

    std::vector<std::thread> hilos;

    for(int i = 0 ; i < cantThreads; i++){
        hilos.emplace_back(&HashMapConcurrente::proceso_thread_promedio, this, std::ref(suma_total), std::ref(elementos_total), std::ref(lista_actual));
    }

    for (auto &hilo : hilos) {
        hilo.join();
    }

    return (float)(suma_total.load()/elementos_total.load());
}

#endif
