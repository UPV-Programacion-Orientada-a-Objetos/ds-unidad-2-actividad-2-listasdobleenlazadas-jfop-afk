/**
 * @file TramaLoad.h
 * @brief Clase derivada que representa tramas de carga (L,X)
 * @author Juan Francisco Ortega Pulido
 * @date 2025
 */

#ifndef TRAMA_LOAD_H
#define TRAMA_LOAD_H

#include "TramaBase.h"
#include "ListaDeCarga.h"
#include "RotorDeMapeo.h"

/**
 * @class TramaLoad
 * @brief Trama que contiene un fragmento de dato (un carácter)
 * 
 * Formato: "L,X" donde X es cualquier carácter (A-Z o espacio).
 * Al procesarse, toma el carácter X, lo pasa por el rotor de mapeo
 * actual, y almacena el resultado en la lista de carga.
 */
class TramaLoad : public TramaBase {
private:
    char caracter;  ///< Carácter contenido en la trama
    
public:
    /**
     * @brief Constructor que almacena el carácter de la trama
     * @param c Carácter a procesar (ej. 'H', 'O', ' ')
     */
    TramaLoad(char c) : caracter(c) {}
    
    /**
     * @brief Destructor (usa el de la clase base)
     */
    ~TramaLoad() {}
    
    /**
     * @brief Procesa la trama: mapea el carácter y lo inserta en la lista
     * @param carga Lista donde se inserta el carácter decodificado
     * @param rotor Rotor usado para mapear el carácter
     * 
     * Flujo:
     * 1. Obtiene el carácter mapeado según la rotación actual del rotor
     * 2. Inserta el resultado en la lista de carga
     */
    void procesar(ListaDeCarga* carga, RotorDeMapeo* rotor);
};

#endif // TRAMA_LOAD_H