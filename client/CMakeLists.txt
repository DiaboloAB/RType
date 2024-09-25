cmake_minimum_required(VERSION 3.10)  # Version minimale requise de CMake
project(r-type_client)                # Nom du projet

# Ajouter les fichiers sources
set(SOURCES
    src/main.cpp
)

# Créer l'exécutable à partir des fichiers sources
add_executable(r-type_client ${SOURCES})

target_include_directories(r-type_client PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
