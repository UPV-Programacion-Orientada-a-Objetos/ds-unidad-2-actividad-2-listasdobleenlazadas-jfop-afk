/**
 * @file RotorDeMapeo.cpp
 * @brief Implementación de la clase RotorDeMapeo
 */

#include "RotorDeMapeo.h"
#include <iostream>

RotorDeMapeo::RotorDeMapeo() : cabeza(0), tamanio(0) {
    // Alfabeto A-Z + espacio (27 caracteres)
    const char alfabeto[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ";
    int longitud = 27;
    
    NodoRotor* anterior = 0;
    NodoRotor* primero = 0;
    
    // Crear la lista circular
    for (int i = 0; i < longitud; i++) {
        NodoRotor* nuevo = new NodoRotor(alfabeto[i]);
        
        if (i == 0) {
            primero = nuevo;
            cabeza = nuevo;  // Inicialmente, cabeza apunta a 'A'
        } else {
            anterior->siguiente = nuevo;
            nuevo->previo = anterior;
        }
        
        anterior = nuevo;
        tamanio++;
    }
    
    // Cerrar el círculo: último nodo conecta con el primero
    if (anterior && primero) {
        anterior->siguiente = primero;
        primero->previo = anterior;
    }
}

RotorDeMapeo::~RotorDeMapeo() {
    if (!cabeza) return;
    
    // Romper el círculo para evitar bucle infinito
    NodoRotor* ultimo = cabeza->previo;
    ultimo->siguiente = 0;
    
    // Eliminar todos los nodos
    NodoRotor* actual = cabeza;
    while (actual) {
        NodoRotor* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }
}

void RotorDeMapeo::rotar(int n) {
    if (!cabeza) return;
    
    // Normalizar n al rango [-tamanio, tamanio]
    int pasos = n % tamanio;
    
    // Rotar hacia la derecha (positivo)
    if (pasos > 0) {
        for (int i = 0; i < pasos; i++) {
            cabeza = cabeza->siguiente;
        }
    }
    // Rotar hacia la izquierda (negativo)
    else if (pasos < 0) {
        for (int i = 0; i > pasos; i--) {
            cabeza = cabeza->previo;
        }
    }
}

char RotorDeMapeo::getMapeo(char entrada) {
    if (!cabeza) return entrada;
    
    // Buscar el carácter de entrada en el rotor
    NodoRotor* actual = cabeza;
    int posicion = 0;
    bool encontrado = false;
    
    for (int i = 0; i < tamanio; i++) {
        if (actual->dato == entrada) {
            encontrado = true;
            posicion = i;
            break;
        }
        actual = actual->siguiente;
    }
    
    // Si no se encuentra, devolver sin mapear
    if (!encontrado) return entrada;
    
    // El mapeo: el carácter en la posición 'posicion' desde cabeza
    // se mapea al carácter que está en esa misma posición desde el inicio original
    // 
    // LÓGICA SIMPLIFICADA: 
    // Si el rotor no ha rotado, cada letra se mapea a sí misma.
    // Si rotó +2, entonces 'A' (que ahora está 2 posiciones antes de cabeza)
    // se mapea a lo que cabeza apunta (ej. 'C').
    //
    // Para implementar esto correctamente:
    // 1. Encontramos dónde está el carácter de entrada (ya hecho)
    // 2. Devolvemos el carácter que está en la posición cero (cabeza)
    //    ajustado por la posición encontrada
    
    // Forma directa: el desplazamiento es cuánto se movió la cabeza
    // Si cabeza apunta a 'C' (rotación +2), entonces:
    // - 'A' está 2 posiciones antes de 'C', se mapea a 'A' + 2 = 'C'
    // - 'B' está 2 posiciones antes de 'D', se mapea a 'B' + 2 = 'D'
    
    // Encontrar el carácter base (el que estaba originalmente en posición 0)
    NodoRotor* baseOriginal = cabeza;
    for (int i = 0; i < tamanio; i++) {
        if (baseOriginal->dato == 'A') {
            break;
        }
        baseOriginal = baseOriginal->siguiente;
    }
    
    // Calcular cuántas posiciones está 'entrada' desde baseOriginal
    actual = baseOriginal;
    int distancia = 0;
    for (int i = 0; i < tamanio; i++) {
        if (actual->dato == entrada) {
            distancia = i;
            break;
        }
        actual = actual->siguiente;
    }
    
    // El resultado es el carácter en cabeza avanzado 'distancia' posiciones
    NodoRotor* resultado = cabeza;
    for (int i = 0; i < distancia; i++) {
        resultado = resultado->siguiente;
    }
    
    return resultado->dato;
}

void RotorDeMapeo::mostrarRotor() {
    if (!cabeza) {
        std::cout << "Rotor vacio" << std::endl;
        return;
    }
    
    std::cout << "Rotor (cabeza en '" << cabeza->dato << "'): ";
    NodoRotor* actual = cabeza;
    for (int i = 0; i < tamanio; i++) {
        std::cout << actual->dato;
        if (i < tamanio - 1) std::cout << "-";
        actual = actual->siguiente;
    }
    std::cout << std::endl;
}