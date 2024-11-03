set(BINARY_NAME "power4")

add_executable(${BINARY_NAME} src/main.cpp)

target_link_libraries(${BINARY_NAME} PRIVATE Holtzman)

set_target_properties(${BINARY_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../bonus/power4"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/../bonus/power4"
)
