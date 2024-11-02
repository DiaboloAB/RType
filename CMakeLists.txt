cmake_minimum_required(VERSION 3.10)

project(RType VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(engine)

add_subdirectory(rtypeServer)
add_subdirectory(rtypeClient)

option(BONUS "Build bonus features" OFF)

if (BONUS)
    add_subdirectory(bonus/power4)
endif()

include(CPack)
