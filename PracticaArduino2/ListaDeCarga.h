/**
 * @file ListaDeCarga.h
 * @brief Lista doblemente enlazada para almacenar caracteres decodificados
 * @author Juan Francisco Ortega Pulido
 * @date 2025
 */

#ifndef LISTA_DE_CARGA_H
#define LISTA_DE_CARGA_H

/**
 * @struct NodoCarga
 * @brief Nodo de la lista doblemente enlazada
 */
struct NodoCarga {
    char dato;              ///< Carácter decodificado
    NodoCarga* siguiente;   ///< Puntero al siguiente nodo
    NodoCarga* previo;      ///< Puntero al nodo anterior
    
    /**
     * @brief Constructor del nodo
     * @param c Carácter a almacenar
     */
    NodoCarga(char c) : dato(c), siguiente(0), previo(0) {}
};

/**
 * @class ListaDeCarga
 * @brief Lista doblemente enlazada para almacenar el mensaje decodificado
 * 
 * Esta lista mantiene el orden de llegada de los caracteres decodificados.
 * Se inserta siempre al final para preservar la secuencia del mensaje.
 */
class ListaDeCarga {
private:
    NodoCarga* cabeza;      ///< Primer nodo de la lista
    NodoCarga* cola;        ///< Último nodo de la lista
    int tamanio;            ///< Número de caracteres almacenados
    
public:
    /**
     * @brief Constructor que inicializa una lista vacía
     */
    ListaDeCarga();
    
    /**
     * @brief Destructor que libera toda la memoria
     */
    ~ListaDeCarga();
    
    /**
     * @brief Inserta un carácter al final de la lista
     * @param dato Carácter a insertar
     * 
     * Mantiene el orden de llegada de los fragmentos decodificados.
     */
    void insertarAlFinal(char dato);
    
    /**
     * @brief Imprime el mensaje completo ensamblado
     * 
     * Recorre toda la lista e imprime cada carácter en orden.
     */
    void imprimirMensaje();
    
    /**
     * @brief Obtiene el tamaño actual de la lista
     * @return Número de caracteres almacenados
     */
    int getTamanio() const { return tamanio; }
    
    /**
     * @brief Verifica si la lista está vacía
     * @return true si no hay elementos, false en caso contrario
     */
    bool estaVacia() const { return cabeza == 0; }
};

#endif // LISTA_DE_CARGA_H