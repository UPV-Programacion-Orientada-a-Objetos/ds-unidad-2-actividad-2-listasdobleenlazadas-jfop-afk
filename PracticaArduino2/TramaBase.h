/**
 * @file TramaBase.h
 * @brief Clase base abstracta para el sistema de tramas PRT-7
 * @author Juan Francisco Ortega Pulido
 * @date 2025
 */

#ifndef TRAMA_BASE_H
#define TRAMA_BASE_H

// Forward declarations para evitar dependencias circulares
class ListaDeCarga;
class RotorDeMapeo;

/**
 * @class TramaBase
 * @brief Clase abstracta que define la interfaz para todas las tramas del protocolo PRT-7
 * 
 * Esta clase sirve como base polimórfica para los dos tipos de tramas:
 * - TramaLoad: Carga datos
 * - TramaMap: Modifica el rotor de mapeo
 */
class TramaBase {
public:
    /**
     * @brief Destructor virtual obligatorio para polimorfismo
     * 
     * CRÍTICO: Al usar punteros de tipo TramaBase* que apuntan a objetos
     * derivados (TramaLoad*, TramaMap*), necesitamos un destructor virtual
     * para garantizar que se llame el destructor correcto al hacer delete.
     */
    virtual ~TramaBase() {}
    
    /**
     * @brief Método virtual puro para procesar la trama
     * @param carga Puntero a la lista que almacena los datos decodificados
     * @param rotor Puntero al rotor de mapeo circular
     * 
     * Este método DEBE ser implementado por todas las clases derivadas.
     * Define el comportamiento específico de cada tipo de trama.
     */
    virtual void procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) = 0;
};

#endif // TRAMA_BASE_H