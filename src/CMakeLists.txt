# Find the Asio package (assuming Asio is installed system-wide or its path is known)
find_package(Asio REQUIRED)
find_package(glfw3 REQUIRED)
find_package(SFML REQUIRED COMPONENTS network window graphics system)

# Create the executable
add_executable(rType)

# Set the C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable position-independent code for shared libraries
set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)

# define where the resources are
file(GLOB_RECURSE SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
)

# Add the source files to the target
target_sources(rType
    PRIVATE
    ${SOURCES}
)

target_include_directories(rType
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/includes
)

# Link Asio library
target_link_libraries(rType
    PRIVATE
    asio::asio
    glfw
    sfml-graphics
    sfml-audio
    sfml-network
)

install(TARGETS rType)
