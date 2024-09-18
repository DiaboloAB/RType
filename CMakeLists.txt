cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project(rType)

# Disable developer warnings for CMake
set(CMAKE_SUPPRESS_DEVELOPER_WARNINGS 1 CACHE INTERNAL "No dev warnings")

# The default name of the generated component
set(CMAKE_INSTALL_DEFAULT_COMPONENT_NAME "default")

# Export all the compile commands
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# If ccache is installed, use to speed up the build
find_program(CCACHE_FOUND ccache HINTS /bin /usr/bin)
if(CCACHE_FOUND)
	set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
	set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
endif()


add_compile_options(
    -Wall
	-Wextra
)

# Specify that the final executable should be in the root directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

add_subdirectory(src)
