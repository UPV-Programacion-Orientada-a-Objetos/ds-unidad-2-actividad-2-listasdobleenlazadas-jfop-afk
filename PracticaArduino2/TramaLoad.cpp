/**
 * @file TramaLoad.cpp
 * @brief Implementación de la clase TramaLoad
 */

#include "TramaLoad.h"
#include <iostream>

void TramaLoad::procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) {
    // Obtener el carácter mapeado según la rotación actual del rotor
    char decodificado = rotor->getMapeo(caracter);
    
    // Insertar en la lista de carga
    carga->insertarAlFinal(decodificado);
    
    // Mostrar información de debug
    std::cout << "Fragmento '" << caracter << "' decodificado como '" 
              << decodificado << "'. Mensaje: [";
    carga->imprimirMensaje();
    std::cout << "]" << std::endl;
}