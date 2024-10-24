cmake_minimum_required(VERSION 3.10)

project(RType VERSION 1.0)

# find_package(Asio REQUIRED)
# find_package(glfw3 REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


add_subdirectory(engine)
add_subdirectory(libs/mobs)
add_subdirectory(libs/mlg)

add_executable(r-type_client
    src/main.cpp
)

add_executable(r-type_server
    src/mainServer.cpp
    src/server/Server.cpp
)

target_link_libraries(r-type_server PRIVATE
    RTypeEngine
    mobs::mobs
    mlg::mlg
)

target_link_libraries(r-type_client PRIVATE
    RTypeEngine
    mobs::mobs
    mlg::mlg
    # asio::asio
    # sfml-graphics
    # sfml-audio
    # sfml-network
)

include(CPack)

target_include_directories(r-type_client PUBLIC
    "${PROJECT_BINARY_DIR}"
    "${PROJECT_SOURCE_DIR}/engine/src"
)

target_include_directories(r-type_server PUBLIC
    "${PROJECT_BINARY_DIR}"
    "${PROJECT_SOURCE_DIR}/engine/src"
    "${PROJECT_SOURCE_DIR}/src/server"
)

set_target_properties(r-type_client
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../"
)

set_target_properties(r-type_server
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../"
)
