/**
 * @file ListaDeCarga.cpp
 * @brief Implementación de la clase ListaDeCarga
 */

#include "ListaDeCarga.h"
#include <iostream>

ListaDeCarga::ListaDeCarga() : cabeza(0), cola(0), tamanio(0) {}

ListaDeCarga::~ListaDeCarga() {
    NodoCarga* actual = cabeza;
    while (actual) {
        NodoCarga* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }
}

void ListaDeCarga::insertarAlFinal(char dato) {
    NodoCarga* nuevo = new NodoCarga(dato);
    
    if (!cabeza) {
        // Lista vacía: el nuevo nodo es cabeza y cola
        cabeza = nuevo;
        cola = nuevo;
    } else {
        // Insertar después de cola
        cola->siguiente = nuevo;
        nuevo->previo = cola;
        cola = nuevo;
    }
    
    tamanio++;
}

void ListaDeCarga::imprimirMensaje() {
    if (!cabeza) {
        std::cout << "[Lista vacia]" << std::endl;
        return;
    }
    
    NodoCarga* actual = cabeza;
    while (actual) {
        std::cout << actual->dato;
        actual = actual->siguiente;
    }
}