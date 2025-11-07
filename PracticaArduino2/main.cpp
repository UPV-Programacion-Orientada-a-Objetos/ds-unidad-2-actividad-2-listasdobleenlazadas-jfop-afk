/**
 * @file main.cpp
 * @brief Programa principal del Decodificador PRT-7
 * @author Juan Francisco Ortega Pulido
 * @date 2025
 * 
 * Este programa lee tramas del puerto serial conectado a un Arduino,
 * procesa las instrucciones de carga y mapeo, y ensambla el mensaje oculto.
 */

#include <iostream>
#include <cstdlib>  // Para atoi
#include "SerialReader.h"
#include "ListaDeCarga.h"
#include "RotorDeMapeo.h"
#include "TramaBase.h"
#include "TramaLoad.h"
#include "TramaMap.h"

#ifdef _WIN32
    #include <windows.h>
    #define SLEEP(ms) Sleep(ms)
#else
    #include <unistd.h>
    #define SLEEP(ms) usleep((ms) * 1000)
#endif

/**
 * @brief Parsea una línea de texto y crea la trama correspondiente
 * @param linea Cadena con formato "L,X" o "M,N"
 * @return Puntero a TramaBase (TramaLoad o TramaMap) o NULL si hay error
 * 
 * Ejemplo: "L,H" -> TramaLoad('H')
 *          "M,2" -> TramaMap(2)
 */
TramaBase* parsearTrama(char* linea) {
    // Verificar que la línea no esté vacía
    if (linea[0] == '\0') return 0;
    
    // Primer carácter: tipo de trama
    char tipo = linea[0];
    
    // Debe haber una coma
    if (linea[1] != ',') {
        std::cerr << "Error: Formato invalido (falta coma)" << std::endl;
        return 0;
    }
    
    // El dato está después de la coma
    char* dato = &linea[2];
    
    if (tipo == 'L') {
        // Trama de carga: L,X
        if (dato[0] == '\0') {
            std::cerr << "Error: Trama LOAD sin caracter" << std::endl;
            return 0;
        }
        
        // Manejar el caso especial del espacio: "L,Space" o "L, "
        char caracter = dato[0];
        if (dato[0] == 'S' && dato[1] == 'p' && dato[2] == 'a' && 
            dato[3] == 'c' && dato[4] == 'e') {
            caracter = ' ';
        }
        
        return new TramaLoad(caracter);
    } 
    else if (tipo == 'M') {
        // Trama de mapeo: M,N
        if (dato[0] == '\0') {
            std::cerr << "Error: Trama MAP sin valor" << std::endl;
            return 0;
        }
        
        // Convertir a entero manualmente (sin atoi para mayor control)
        int num = 0;
        int signo = 1;
        int i = 0;
        
        // Verificar signo
        if (dato[i] == '-') {
            signo = -1;
            i++;
        } else if (dato[i] == '+') {
            i++;
        }
        
        // Convertir dígitos
        while (dato[i] >= '0' && dato[i] <= '9') {
            num = num * 10 + (dato[i] - '0');
            i++;
        }
        
        num *= signo;
        return new TramaMap(num);
    }
    
    std::cerr << "Error: Tipo de trama desconocido: " << tipo << std::endl;
    return 0;
}

/**
 * @brief Función principal del programa
 */
int main() {
    std::cout << "==================================================" << std::endl;
    std::cout << "  DECODIFICADOR PRT-7 - Sistema de Ciberseguridad" << std::endl;
    std::cout << "==================================================" << std::endl;
    std::cout << std::endl;
    
    // Solicitar puerto al usuario
    std::cout << "Ingrese el puerto serial (ej. COM3 o /dev/ttyUSB0): ";
    char nombrePuerto[50];
    std::cin.getline(nombrePuerto, 50);
    
    // Crear el lector serial
    SerialReader serial(nombrePuerto);
    
    std::cout << std::endl;
    std::cout << "Iniciando Decodificador PRT-7. Conectando a puerto..." << std::endl;
    
    if (!serial.conectar()) {
        std::cerr << "Error: No se pudo conectar al puerto serial" << std::endl;
        std::cerr << "Verifique que:" << std::endl;
        std::cerr << "  1. El Arduino este conectado" << std::endl;
        std::cerr << "  2. El nombre del puerto sea correcto" << std::endl;
        std::cerr << "  3. No haya otra aplicacion usando el puerto" << std::endl;
        return 1;
    }
    
    std::cout << "Conexion establecida. Esperando tramas..." << std::endl;
    std::cout << std::endl;
    
    // Inicializar estructuras de datos
    ListaDeCarga miLista;
    RotorDeMapeo miRotor;
    
    // Buffer para leer líneas
    char buffer[100];
    int tramasRecibidas = 0;
    
    // Bucle principal: leer y procesar tramas
    while (true) {
        if (serial.leerLinea(buffer, 100)) {
            tramasRecibidas++;
            
            std::cout << "Trama recibida: [" << buffer << "] -> Procesando... -> ";
            
            // Parsear la trama
            TramaBase* trama = parsearTrama(buffer);
            
            if (trama) {
                // Ejecutar el procesamiento polimórfico
                trama->procesar(&miLista, &miRotor);
                
                // Liberar memoria de la trama
                delete trama;
            } else {
                std::cout << "Error al parsear trama" << std::endl;
            }
            
            std::cout << std::endl;
        }
        
        // Pequeña pausa para no saturar el CPU
        SLEEP(100);
        
        // Salir después de recibir muchas tramas (para no quedarse colgado)
        // En producción, esto sería una señal de fin de transmisión
        if (tramasRecibidas >= 50) {
            std::cout << "[Limite de tramas alcanzado, finalizando...]" << std::endl;
            break;
        }
    }
    
    // Mostrar resultado final
    std::cout << std::endl;
    std::cout << "---" << std::endl;
    std::cout << "Flujo de datos terminado." << std::endl;
    std::cout << "MENSAJE OCULTO ENSAMBLADO:" << std::endl;
    miLista.imprimirMensaje();
    std::cout << std::endl;
    std::cout << "---" << std::endl;
    std::cout << "Liberando memoria... Sistema apagado." << std::endl;
    
    serial.cerrar();
    return 0;
}