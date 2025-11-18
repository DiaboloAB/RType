set(BINARY_NAME "test3d")

add_executable(${BINARY_NAME} src/main.cpp)

target_link_libraries(${BINARY_NAME} PRIVATE Holtzman)

set_target_properties(${BINARY_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../test-3d"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/../test-3d"
)

if (NOT WIN32)
    add_custom_command(TARGET ${BINARY_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E create_symlink
        "$<TARGET_FILE:${BINARY_NAME}>"
        "${CMAKE_BINARY_DIR}/../test3d"
    )
endif()