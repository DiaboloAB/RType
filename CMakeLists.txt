cmake_minimum_required(VERSION 3.10)

project(RType VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(BINARY_NAME "r-type_client")

if (POLICY CMP0091)
    cmake_policy(SET CMP0091 NEW)
endif ()

add_subdirectory(engine)

add_executable(${BINARY_NAME}
    src/main.cpp
)

target_include_directories(${BINARY_NAME} PUBLIC
    "${PROJECT_BINARY_DIR}"
)

target_link_libraries(${BINARY_NAME} PRIVATE
    Holtzman
)

set_target_properties(${BINARY_NAME}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../"
)

include(CPack)
