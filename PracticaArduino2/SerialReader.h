/**
 * @file SerialReader.h
 * @brief Clase para leer datos del puerto serial
 * @author Juan Francisco Ortega Pulido
 * @date 2025
 */

#ifndef SERIAL_READER_H
#define SERIAL_READER_H

/**
 * @class SerialReader
 * @brief Maneja la comunicación con el puerto serial del Arduino
 * 
 * Esta clase abstrae la complejidad de la comunicación serial.
 * En sistemas Windows usa la API de Win32, en Linux/Mac usa termios.
 */
class SerialReader {
private:
    void* handle;           ///< Handle del puerto (void* para independencia de plataforma)
    char* puerto;           ///< Nombre del puerto (ej. "COM3" o "/dev/ttyUSB0")
    bool conectado;         ///< Estado de la conexión
    
    /**
     * @brief Copia una cadena manualmente (sin usar std::string)
     * @param destino Buffer de destino
     * @param origen Cadena fuente
     */
    void copiarCadena(char* destino, const char* origen);
    
public:
    /**
     * @brief Constructor que inicializa con el nombre del puerto
     * @param nombrePuerto Nombre del puerto serial (ej. "COM3")
     */
    SerialReader(const char* nombrePuerto);
    
    /**
     * @brief Destructor que cierra la conexión
     */
    ~SerialReader();
    
    /**
     * @brief Abre y configura el puerto serial
     * @return true si se conectó exitosamente, false en caso contrario
     */
    bool conectar();
    
    /**
     * @brief Lee una línea del puerto serial
     * @param buffer Buffer donde se almacenará la línea leída
     * @param maxLen Tamaño máximo del buffer
     * @return true si se leyó una línea completa, false si no hay datos
     * 
     * Lee hasta encontrar '\n' o hasta llenar el buffer.
     */
    bool leerLinea(char* buffer, int maxLen);
    
    /**
     * @brief Cierra el puerto serial
     */
    void cerrar();
    
    /**
     * @brief Verifica si el puerto está conectado
     * @return true si está conectado, false en caso contrario
     */
    bool estaConectado() const { return conectado; }
};

#endif // SERIAL_READER_H