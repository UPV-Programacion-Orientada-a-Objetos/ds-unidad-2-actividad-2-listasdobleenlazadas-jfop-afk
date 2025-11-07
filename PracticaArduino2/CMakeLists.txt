cmake_minimum_required(VERSION 3.10)

# Nombre del proyecto
project(DecodificadorPRT7 VERSION 1.0 LANGUAGES CXX)

# Estándar de C++
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Archivos fuente
set(SOURCES
    main.cpp
    RotorDeMapeo.cpp
    ListaDeCarga.cpp
    TramaLoad.cpp
    TramaMap.cpp
    SerialReader.cpp
)

# Archivos de cabecera
set(HEADERS
    TramaBase.h
    RotorDeMapeo.h
    ListaDeCarga.h
    TramaLoad.h
    TramaMap.h
    SerialReader.h
)

# Crear el ejecutable
add_executable(decodificador ${SOURCES} ${HEADERS})

# Configuración específica de plataforma
if(WIN32)
    # Windows: No necesita librerías adicionales para serial (usa Win32 API)
    message(STATUS "Compilando para Windows")
elseif(UNIX)
    # Linux/Mac: Puede necesitar pthread
    message(STATUS "Compilando para Unix/Linux")
    target_link_libraries(decodificador pthread)
endif()

# Opciones de compilación
if(MSVC)
    target_compile_options(decodificador PRIVATE /W4)
else()
    target_compile_options(decodificador PRIVATE -Wall -Wextra -pedantic)
endif()

# Instalación
install(TARGETS decodificador DESTINATION bin)

# Documentación con Doxygen (opcional)
find_package(Doxygen)
if(DOXYGEN_FOUND)
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
    
    if(EXISTS ${DOXYGEN_IN})
        configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
        message(STATUS "Doxygen configurado, use 'make docs' para generar documentación")
        
        add_custom_target(docs
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generando documentación con Doxygen"
            VERBATIM
        )
    endif()
else()
    message(WARNING "Doxygen no encontrado, no se podrá generar documentación")
endif()

# Información de compilación
message(STATUS "==========================================")
message(STATUS "Proyecto: ${PROJECT_NAME} v${PROJECT_VERSION}")
message(STATUS "Compilador: ${CMAKE_CXX_COMPILER}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "==========================================")