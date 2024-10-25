set(BINARY_NAME "r-type_server")

add_executable(${BINARY_NAME} src/main.cpp
    src/server/ArgParser.cpp
    src/server/MainServer.cpp
)

target_include_directories(${BINARY_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/server/
)

target_link_libraries(${BINARY_NAME} PRIVATE Holtzman
    dimension::dimension)

set_target_properties(${BINARY_NAME}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../rtypeServer"
)

# Create a symlink in the parent directory pointing to the binary
add_custom_command(TARGET ${BINARY_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E create_symlink
    "$<TARGET_FILE:${BINARY_NAME}>"         # Use generator expression to get the full path of the executable
    "${CMAKE_BINARY_DIR}/../r-type_server"  # Symlink location
)