#ifndef CHM_CPP
#define CHM_CPP

#include <vector>
#include <iostream>
#include <fstream>
#include <thread>

#include "CargarArchivos.hpp"

int cargarArchivo(
    HashMapConcurrente &hashMap,
    std::string filePath
) {
    std::fstream file;
    int cant = 0;
    std::string palabraActual;

    // Abro el archivo.
    file.open(filePath, file.in);
    if (!file.is_open()) {
        std::cerr << "Error al abrir el archivo '" << filePath << "'" << std::endl;
        return -1;
    }
    while (file >> palabraActual) {
        // Completar (Ejercicio 4)
        cant++;
        //printf("%s\n", palabraActual.c_str());
        hashMap.incrementar(palabraActual);
        //printf("se inserto %s, palabra numero %d\n", palabraActual.c_str(), cant);
    }
    // Cierro el archivo.
    //printf("se termino de leer\n");
    if (!file.eof()) {
        std::cerr << "Error al leer el archivo" << std::endl;
        file.close();
        return -1;
    }
    //printf("cerrando archivo\n");
    file.close();
    //printf("FIN\n");
    return cant;
}

void proceso_thread(std::atomic<unsigned int> &archivo_actual, HashMapConcurrente &hashMap, std::vector<std::string> &filePaths) {
    while (true) {
        unsigned int index = archivo_actual.fetch_add(1);
        if (index >= filePaths.size()) break;
        cargarArchivo(hashMap, filePaths[index]);
    }
}

void cargarMultiplesArchivos(
    HashMapConcurrente &hashMap,
    unsigned int cantThreads,
    std::vector<std::string> filePaths
) {
    // Completar (Ejercicio 4)
    std::atomic<unsigned int> archivo_actual(0);

    std::vector<std::thread> hilos;

    for(int i = 0 ; i < cantThreads; i++){
        hilos.emplace_back(proceso_thread, std::ref(archivo_actual), std::ref(hashMap), std::ref(filePaths));
    }

    for (auto &hilo : hilos) {
        hilo.join();
    }

    return;
}

#endif
