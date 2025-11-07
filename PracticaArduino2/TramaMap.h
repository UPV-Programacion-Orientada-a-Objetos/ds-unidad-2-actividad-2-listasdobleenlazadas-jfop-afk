/**
 * @file TramaMap.h
 * @brief Clase derivada que representa tramas de mapeo (M,N)
 * @author Juan Francisco Ortega Pulido
 * @date 2025
 */

#ifndef TRAMA_MAP_H
#define TRAMA_MAP_H

#include "TramaBase.h"
#include "ListaDeCarga.h"
#include "RotorDeMapeo.h"

/**
 * @class TramaMap
 * @brief Trama que modifica la rotación del rotor de mapeo
 * 
 * Formato: "M,N" donde N es un número entero (puede ser negativo).
 * Al procesarse, rota el rotor N posiciones, cambiando el mapeo
 * de todos los caracteres subsecuentes.
 */
class TramaMap : public TramaBase {
private:
    int rotacion;   ///< Número de posiciones a rotar (+ o -)
    
public:
    /**
     * @brief Constructor que almacena la cantidad de rotación
     * @param n Número de posiciones a rotar (ej. 2, -3)
     */
    TramaMap(int n) : rotacion(n) {}
    
    /**
     * @brief Destructor (usa el de la clase base)
     */
    ~TramaMap() {}
    
    /**
     * @brief Procesa la trama: rota el rotor
     * @param carga Lista de carga (no se usa en esta trama)
     * @param rotor Rotor que se rotará
     * 
     * Flujo:
     * 1. Llama a rotor->rotar(rotacion)
     * 2. Esto cambia el mapeo para todas las TramaLoad subsecuentes
     */
    void procesar(ListaDeCarga* carga, RotorDeMapeo* rotor);
};

#endif // TRAMA_MAP_H