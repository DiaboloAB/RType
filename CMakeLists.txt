cmake_minimum_required(VERSION 3.30)

project(RType VERSION 1.0)

# find_package(Asio REQUIRED)
# find_package(glfw3 REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if (POLICY CMP0091)
    cmake_policy(SET CMP0091 NEW)
endif ()

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

install(TARGETS r-type_client DESTINATION bin)
install(TARGETS r-type_server DESTINATION bin)

# Specify the directory where your assets are stored
set(GAME_ASSETS_DIR "./assets")

# Install the assets to the target directory in the package
install(DIRECTORY ${GAME_ASSETS_DIR} DESTINATION "bin/")


# Include CPack for packaging
include(CPack)

# Set the project name and version
set(CPACK_PACKAGE_NAME "RType")
set(CPACK_PACKAGE_VERSION "1.0")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "RType by Les marmoteurs")
set(CPACK_PACKAGE_VENDOR "Les marmoteurs inc.")

# Optionally set other options for packaging type (ZIP, DEB, RPM, etc.)
set(CPACK_GENERATOR "ZIP")

# Specify the installation directory structure
set(CPACK_PACKAGE_INSTALL_DIRECTORY "MyGame")


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
