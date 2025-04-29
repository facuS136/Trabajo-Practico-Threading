#ifndef HMC_HPP
#define HMC_HPP

#include <mutex>
#include <semaphore.h>
#include <array>
#include <atomic>
#include <string>
#include <vector>

#include "ListaAtomica.hpp"

typedef std::pair<std::string, unsigned int> hashMapPair;

class HashMapConcurrente {
 public:
    static constexpr int cantLetras = 26;

    HashMapConcurrente();

    void incrementar(std::string clave);
    std::vector<std::string> claves();
    unsigned int valor(std::string clave);

    float promedio();
    float promedioParalelo(unsigned int cantThreads);



 private:
    ListaAtomica<hashMapPair> *tabla[HashMapConcurrente::cantLetras];

    static unsigned int hashIndex(std::string clave);
   void proceso_thread_promedio(std::atomic<unsigned int> &suma_total, std::atomic<unsigned int> &elementos_total, std::atomic<unsigned int> &lista_actual);
   //
    std::vector<sem_t> _semaforos;
    
};

#endif  /* HMC_HPP */
