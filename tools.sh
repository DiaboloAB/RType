#!/bin/bash

usage()
{
    echo "Usage: $0 <build|build-sdl|build-off|build-test|run-test|pack|clean|rebuild>"
}

COMMAND=$1

if [ "$COMMAND" == "build" ]; then

    mkdir build
    cd build
    conan profile detect --force
    conan install .. --output-folder=conan --build=missing -c "tools.system.package_manager:mode=install" -c "tools.system.package_manager:sudo=true"
    cmake .. -DCMAKE_TOOLCHAIN_FILE=conan/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
    cmake --build . -- -j 4

elif [ "$COMMAND" == "build-sdl" ]; then

    mkdir build
    cd build
    conan profile detect --force
    conan install .. --output-folder=conan --build=missing -c "tools.system.package_manager:mode=install" -c "tools.system.package_manager:sudo=true" -o graphics=SDL
    cmake .. -DCMAKE_TOOLCHAIN_FILE=conan/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release -DGRAPHICS=SDL
    cmake --build . -- -j 4

elif [ "$COMMAND" == "build-off" ]; then

    mkdir build
    cd build
    conan profile detect --force
    conan install .. --output-folder=conan --build=missing -c "tools.system.package_manager:mode=install" -c "tools.system.package_manager:sudo=true" -o graphics=OFF
    cmake .. -DCMAKE_TOOLCHAIN_FILE=conan/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release -DGRAPHICS=OFF
    cmake --build . -- -j 4

elif [ "$COMMAND" == "build-test" ]; then

    conan profile detect --force
    conan install . --output-folder=build/conan --build=missing -c "tools.system.package_manager:mode=install" -c "tools.system.package_manager:sudo=true"
    cd build
    cmake .. -DCMAKE_TOOLCHAIN_FILE=conan/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release -DTESTS=ON
    cmake --build .

elif [ "$COMMAND" == "run-test" ]; then

    echo "Running tests..."
    cd build
    ./libs/mobs/test_mobs
    ./libs/mlg/test_mlg
    ./engine/test_engine
    cd ..

elif [ "$COMMAND" == "pack" ]; then

    conan profile detect --force
    conan install . --output-folder=build/conan --build=missing -c "tools.system.package_manager:mode=install" -c "tools.system.package_manager:sudo=true"
    cd build
    cmake .. -DCMAKE_TOOLCHAIN_FILE=conan/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
    cpack --config CPackConfig.cmake

elif [ "$COMMAND" == "clean" ]; then

    echo "Cleaning project..."
    rm -rf build
    rm r-type_client
    rm r-type_server
    rm CMakeUserPresets.json

elif [ "$COMMAND" == "rebuild" ]; then

    echo "Rebuilding project..."
    $0 clean
    $0 build

else
    usage
fi
