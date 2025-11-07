/**
 * @file RotorDeMapeo.h
 * @brief Implementación de una Lista Circular Doblemente Enlazada para el mapeo de caracteres
 * @author Juan Francisco Ortega Pulido
 * @date 2025
 */

#ifndef ROTOR_DE_MAPEO_H
#define ROTOR_DE_MAPEO_H

/**
 * @struct NodoRotor
 * @brief Nodo individual de la lista circular que contiene un carácter
 */
struct NodoRotor {
    char dato;              ///< Carácter almacenado (A-Z o espacio)
    NodoRotor* siguiente;   ///< Puntero al siguiente nodo (circular)
    NodoRotor* previo;      ///< Puntero al nodo anterior (circular)
    
    /**
     * @brief Constructor del nodo
     * @param c Carácter a almacenar
     */
    NodoRotor(char c) : dato(c), siguiente(0), previo(0) {}
};

/**
 * @class RotorDeMapeo
 * @brief Lista circular doblemente enlazada que simula un disco de cifrado
 * 
 * Funciona como una "Rueda de César" dinámica. Contiene el alfabeto A-Z más
 * el espacio, y puede rotar para cambiar el mapeo de caracteres.
 * 
 * Ejemplo: Si cabeza apunta a 'A' y rotamos +2, cabeza apuntará a 'C'.
 * Entonces 'A' se mapeará a 'C', 'B' a 'D', etc.
 */
class RotorDeMapeo {
private:
    NodoRotor* cabeza;      ///< Posición "cero" actual del rotor
    int tamanio;            ///< Número total de caracteres en el rotor
    
public:
    /**
     * @brief Constructor que inicializa el rotor con A-Z y espacio
     */
    RotorDeMapeo();
    
    /**
     * @brief Destructor que libera toda la memoria de los nodos
     */
    ~RotorDeMapeo();
    
    /**
     * @brief Rota el rotor N posiciones
     * @param n Número de posiciones a rotar (positivo=derecha, negativo=izquierda)
     * 
     * No mueve los datos, solo cambia el puntero 'cabeza' de forma circular.
     */
    void rotar(int n);
    
    /**
     * @brief Obtiene el carácter mapeado según la rotación actual
     * @param entrada Carácter a mapear
     * @return Carácter resultante después del mapeo
     * 
     * Lógica: Encuentra 'entrada' en el rotor, calcula su distancia desde
     * 'cabeza', y devuelve el carácter que está a esa misma distancia
     * desde la posición cero original.
     */
    char getMapeo(char entrada);
    
    /**
     * @brief Método auxiliar para debug - muestra el estado del rotor
     */
    void mostrarRotor();
};

#endif // ROTOR_DE_MAPEO_H