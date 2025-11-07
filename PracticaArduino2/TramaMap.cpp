/**
 * @file TramaMap.cpp
 * @brief Implementación de la clase TramaMap
 */

#include "TramaMap.h"
#include <iostream>

void TramaMap::procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) {
    // Rotar el rotor según el valor de rotación
    rotor->rotar(rotacion);
    
    // Mostrar información de debug
    std::cout << "ROTANDO ROTOR ";
    if (rotacion > 0) {
        std::cout << "+" << rotacion;
    } else {
        std::cout << rotacion;
    }
    std::cout << std::endl;
}