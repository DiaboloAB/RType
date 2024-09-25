cmake_minimum_required(VERSION 3.10)  # Version minimale requise de CMake
project(r-type_server)                      # Nom du projet

# Ajouter les fichiers sources
set(SOURCES
    main.cpp
    Server.cpp
)

# Créer l'exécutable à partir des fichiers sources
add_executable(r-type_server ${SOURCES})

target_include_directories(r-type_server PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    )
