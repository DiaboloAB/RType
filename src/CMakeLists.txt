# Find the Asio package (assuming Asio is installed system-wide or its path is known)
find_package(Asio REQUIRED)
find_package(GLFW REQUIRED)

add_executable(rType)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)


file(GLOB_RECURSE SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
)

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
    glfw::glfw
)

install(TARGETS rType)
