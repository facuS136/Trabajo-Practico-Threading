#include <vector>
#include "lib/littletest.hpp"

#include "../src/ListaAtomica.hpp"
#include "../src/HashMapConcurrente.hpp"
#include "../src/CargarArchivos.hpp"

// Tests Ejercicio 1

LT_BEGIN_SUITE(TestsEjercicio1)

ListaAtomica<int> l;

void set_up()
{
}

void tear_down()
{
}
LT_END_SUITE(TestsEjercicio1)

LT_BEGIN_TEST(TestsEjercicio1, ListaComienzaVacia)
    LT_CHECK_EQ(l.longitud(), 0);
LT_END_TEST(ListaComienzaVacia)

LT_BEGIN_TEST(TestsEjercicio1, InsertarAgregaElemento)
    l.insertar(42);
    LT_CHECK_EQ(l.longitud(), 1);
LT_END_TEST(InsertarAgregaElemento)

LT_BEGIN_TEST(TestsEjercicio1, InsertarAgregaElementoCorrecto)
    l.insertar(42);
    LT_CHECK_EQ(l[0], 42);
LT_END_TEST(InsertarAgregaElementoCorrecto)

LT_BEGIN_TEST(TestsEjercicio1, InsertarAgregaEnOrden)
    l.insertar(4);
    l.insertar(3);
    l.insertar(2);
    l.insertar(1);
    LT_CHECK_EQ(l.longitud(), 4);
    LT_CHECK_EQ(l[0], 1);
    LT_CHECK_EQ(l[1], 2);
    LT_CHECK_EQ(l[2], 3);
    LT_CHECK_EQ(l[3], 4);
LT_END_TEST(InsertarAgregaEnOrden)

// Tests Ejercicio 2

LT_BEGIN_SUITE(TestsEjercicio2)

HashMapConcurrente hM;

void set_up()
{
}

void tear_down()
{
}
LT_END_SUITE(TestsEjercicio2)

LT_BEGIN_TEST(TestsEjercicio2, ValorEsCorrectoEnHashMapVacio)
    LT_CHECK_EQ(hM.valor("Heladera"), 0);
LT_END_TEST(ValorEsCorrectoEnHashMapVacio)

LT_BEGIN_TEST(TestsEjercicio2, ClavesEsCorrectoEnHashMapVacio)
    std::vector<std::string> actual = hM.claves();
    std::vector<std::string> expected = {};
    LT_CHECK_COLLECTIONS_EQ(actual.begin(), actual.end(), expected.begin());
LT_END_TEST(ClavesEsCorrectoEnHashMapVacio)

LT_BEGIN_TEST(TestsEjercicio2, ValorEsCorrectoTrasUnaInsercion)
    hM.incrementar("Heladera");
    LT_CHECK_EQ(hM.valor("Heladera"), 1);
LT_END_TEST(ValorEsCorrectoTrasUnaInsercion)

LT_BEGIN_TEST(TestsEjercicio2, ClavesEsCorrectoTrasUnaInsercion)
    hM.incrementar("Heladera");
    std::vector<std::string> actual = hM.claves();
    std::vector<std::string> expected = {"Heladera"};
    LT_CHECK_COLLECTIONS_EQ(actual.begin(), actual.end(), expected.begin());
LT_END_TEST(ClavesEsCorrectoTrasUnaInsercion)

LT_BEGIN_TEST(TestsEjercicio2, ValorEsCorrectoTrasDosInsercionesMismaPalabra)
    hM.incrementar("Heladera");
    hM.incrementar("Heladera");
    LT_CHECK_EQ(hM.valor("Heladera"), 2);
LT_END_TEST(ValorEsCorrectoTrasDosInsercionesMismaPalabra)

LT_BEGIN_TEST(TestsEjercicio2, ClavesEsCorrectoTrasDosInsercionesMismaPalabra)
    hM.incrementar("Heladera");
    hM.incrementar("Heladera");
    std::vector<std::string> actual = hM.claves();
    std::vector<std::string> expected = {"Heladera"};
    LT_CHECK_COLLECTIONS_EQ(actual.begin(), actual.end(), expected.begin());
LT_END_TEST(ClavesEsCorrectoTrasDosInsercionesMismaPalabra)

LT_BEGIN_TEST(TestsEjercicio2, ValorEsCorrectoTrasVariasInsercionesMismoBucket)
    hM.incrementar("Heladera");
    hM.incrementar("Heladera");
    hM.incrementar("Lavarropa");
    LT_CHECK_EQ(hM.valor("Heladera"), 2);
    LT_CHECK_EQ(hM.valor("Lavarropa"), 1);
LT_END_TEST(ValorEsCorrectoTrasVariasInsercionesMismoBucket)

LT_BEGIN_TEST(TestsEjercicio2, ClavesEsCorrectoTrasVariasInsercionesMismoBucket)
    hM.incrementar("Heladera");
    hM.incrementar("Heladera");
    hM.incrementar("Lavarropa");
    std::vector<std::string> actual = hM.claves();
    LT_CHECK_EQ(actual.size(), 2);
    LT_CHECK(std::find(actual.begin(), actual.end(), "Heladera") != actual.end());
    LT_CHECK(std::find(actual.begin(), actual.end(), "Lavarropa") != actual.end());
LT_END_TEST(ClavesEsCorrectoTrasVariasInsercionesMismoBucket)

LT_BEGIN_TEST(TestsEjercicio2, ValorEsCorrectoTrasVariasInsercionesDistintoBucket)
    hM.incrementar("Heladera");
    hM.incrementar("Microondas");
    hM.incrementar("Heladera");
    LT_CHECK_EQ(hM.valor("Heladera"), 2);
    LT_CHECK_EQ(hM.valor("Microondas"), 1);
LT_END_TEST(ValorEsCorrectoTrasVariasInsercionesDistintoBucket)

LT_BEGIN_TEST(TestsEjercicio2, ClavesEsCorrectoTrasVariasInsercionesDistintoBucket)
    hM.incrementar("Heladera");
    hM.incrementar("Microondas");
    hM.incrementar("Heladera");
    std::vector<std::string> actual = hM.claves();
    LT_CHECK_EQ(actual.size(), 2);
    LT_CHECK(std::find(actual.begin(), actual.end(), "Heladera") != actual.end());
    LT_CHECK(std::find(actual.begin(), actual.end(), "Microondas") != actual.end());
LT_END_TEST(ClavesEsCorrectoTrasVariasInsercionesDistintoBucket)

// Tests Ejercicio 3

LT_BEGIN_SUITE(TestsEjercicio3)

HashMapConcurrente hM;

void set_up()
{
}

void tear_down()
{
}
LT_END_SUITE(TestsEjercicio3)

LT_BEGIN_TEST(TestsEjercicio3, PromedioEsCorrecto)
    hM.incrementar("Heladera");
    hM.incrementar("Heladera");
    hM.incrementar("Heladera");
    hM.incrementar("Heladera");
    hM.incrementar("Microondas");
    hM.incrementar("Microondas");

    float actual = hM.promedio();
    LT_CHECK_EQ(actual, 3);
LT_END_TEST(PromedioEsCorrecto)

// Completar TEST para caso concurrente

LT_BEGIN_SUITE(TestsEjercicio4)

HashMapConcurrente hM;

void set_up()
{
}

void tear_down()
{
}
LT_END_SUITE(TestsEjercicio4)

LT_BEGIN_TEST(TestsEjercicio4, CargarArchivoFunciona)
    //printf("cargando archivo\n");
    cargarArchivo(hM, "data/test-1");
    //printf("archivo cargado\n");
    LT_CHECK_EQ(hM.valor("Heladera"), 1);
    //printf("igualdad valor correcta\n");
    LT_CHECK_EQ(hM.claves().size(), 5);
    //printf("igualdad claves correcta\n");
LT_END_TEST(CargarArchivoFunciona)

LT_BEGIN_TEST(TestsEjercicio4, CargarMultiplesArchivosFuncionaUnThread)
    cargarMultiplesArchivos(hM, 1, {"data/test-1", "data/test-2", "data/test-3"});
    LT_CHECK_EQ(hM.valor("Heladera"), 2);
    LT_CHECK_EQ(hM.valor("NotebookOMEN"), 3);
    LT_CHECK_EQ(hM.valor("Microondas"), 4);
    LT_CHECK_EQ(hM.claves().size(), 12);
LT_END_TEST(CargarMultiplesArchivosFuncionaUnThread)

LT_BEGIN_TEST(TestsEjercicio4, CargarMultiplesArchivosFuncionaDosThreads)
    cargarMultiplesArchivos(hM, 1, {"data/test-1", "data/test-2", "data/test-3"});
    LT_CHECK_EQ(hM.valor("Heladera"), 2);
    LT_CHECK_EQ(hM.valor("NotebookOMEN"), 3);
    LT_CHECK_EQ(hM.valor("Microondas"), 4);
    LT_CHECK_EQ(hM.claves().size(), 12);
LT_END_TEST(CargarMultiplesArchivosFuncionaDosThreads)

// Ejecutar tests
LT_BEGIN_AUTO_TEST_ENV()
    AUTORUN_TESTS()
LT_END_AUTO_TEST_ENV()
