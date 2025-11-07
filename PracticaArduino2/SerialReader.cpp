/**
 * @file SerialReader.cpp
 * @brief Implementación de SerialReader con soporte multiplataforma
 */

#include "SerialReader.h"
#include <iostream>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <fcntl.h>
    #include <unistd.h>
    #include <termios.h>
#endif

SerialReader::SerialReader(const char* nombrePuerto) : handle(0), conectado(false) {
    // Calcular longitud de la cadena
    int len = 0;
    while (nombrePuerto[len] != '\0') len++;
    
    // Reservar memoria y copiar
    puerto = new char[len + 1];
    copiarCadena(puerto, nombrePuerto);
}

SerialReader::~SerialReader() {
    cerrar();
    delete[] puerto;
}

void SerialReader::copiarCadena(char* destino, const char* origen) {
    int i = 0;
    while (origen[i] != '\0') {
        destino[i] = origen[i];
        i++;
    }
    destino[i] = '\0';
}

bool SerialReader::conectar() {
#ifdef _WIN32
    // Windows: Usar CreateFile de la API Win32
    HANDLE hSerial = CreateFileA(
        puerto,
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );
    
    if (hSerial == INVALID_HANDLE_VALUE) {
        std::cerr << "Error: No se pudo abrir el puerto " << puerto << std::endl;
        return false;
    }
    
    // Configurar parámetros del puerto (9600 baud, 8N1)
    DCB dcbSerialParams = {0};
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    
    if (!GetCommState(hSerial, &dcbSerialParams)) {
        std::cerr << "Error al obtener configuracion del puerto" << std::endl;
        CloseHandle(hSerial);
        return false;
    }
    
    dcbSerialParams.BaudRate = CBR_9600;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;
    
    if (!SetCommState(hSerial, &dcbSerialParams)) {
        std::cerr << "Error al configurar puerto serial" << std::endl;
        CloseHandle(hSerial);
        return false;
    }
    
    // Configurar timeouts
    COMMTIMEOUTS timeouts = {0};
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    SetCommTimeouts(hSerial, &timeouts);
    
    handle = hSerial;
    conectado = true;
    std::cout << "Conectado a " << puerto << std::endl;
    return true;
    
#else
    // Linux/Mac: Usar termios
    int fd = open(puerto, O_RDWR | O_NOCTTY | O_NDELAY);
    
    if (fd == -1) {
        std::cerr << "Error: No se pudo abrir el puerto " << puerto << std::endl;
        return false;
    }
    
    // Configurar termios para 9600 baud, 8N1
    struct termios options;
    tcgetattr(fd, &options);
    
    cfsetispeed(&options, B9600);
    cfsetospeed(&options, B9600);
    
    options.c_cflag |= (CLOCAL | CREAD);
    options.c_cflag &= ~PARENB;
    options.c_cflag &= ~CSTOPB;
    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8;
    
    tcsetattr(fd, TCSANOW, &options);
    
    handle = (void*)(long)fd;
    conectado = true;
    std::cout << "Conectado a " << puerto << std::endl;
    return true;
#endif
}

bool SerialReader::leerLinea(char* buffer, int maxLen) {
    if (!conectado) return false;
    
    int pos = 0;
    char c;
    
#ifdef _WIN32
    HANDLE hSerial = (HANDLE)handle;
    DWORD bytesRead;
    
    while (pos < maxLen - 1) {
        if (!ReadFile(hSerial, &c, 1, &bytesRead, NULL)) {
            return false;
        }
        
        if (bytesRead == 0) {
            // No hay datos disponibles
            if (pos > 0) break;  // Si ya leímos algo, devolver
            return false;        // Si no, indicar que no hay línea
        }
        
        if (c == '\n' || c == '\r') {
            if (pos > 0) break;  // Línea completa
            continue;            // Ignorar CR/LF al inicio
        }
        
        buffer[pos++] = c;
    }
    
#else
    int fd = (int)(long)handle;
    
    while (pos < maxLen - 1) {
        int n = read(fd, &c, 1);
        
        if (n <= 0) {
            if (pos > 0) break;
            return false;
        }
        
        if (c == '\n' || c == '\r') {
            if (pos > 0) break;
            continue;
        }
        
        buffer[pos++] = c;
    }
#endif
    
    buffer[pos] = '\0';
    return pos > 0;
}

void SerialReader::cerrar() {
    if (!conectado) return;
    
#ifdef _WIN32
    CloseHandle((HANDLE)handle);
#else
    close((int)(long)handle);
#endif
    
    conectado = false;
}