set(BINARY_NAME "r-type_server")

add_executable(${BINARY_NAME} src/main.cpp
    src/server/MainServer.cpp
    src/server/parser/ArgParser.cpp
    src/server/rooms/RoomManager.cpp
)

target_include_directories(${BINARY_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/server/
    ${CMAKE_CURRENT_SOURCE_DIR}/src/server/parser/
    ${CMAKE_CURRENT_SOURCE_DIR}/src/server/rooms/
)

target_link_libraries(${BINARY_NAME} PRIVATE Holtzman
    dimension::dimension)

set_target_properties(${BINARY_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../rtypeServer"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/../rtypeServer"
)

if (NOT WIN32)
    add_custom_command(TARGET ${BINARY_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E create_symlink
        "$<TARGET_FILE:${BINARY_NAME}>"
        "${CMAKE_BINARY_DIR}/../r-type_server"
    )
endif()
