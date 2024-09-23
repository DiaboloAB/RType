
#!/bin/bash


if [ "$1" == "clean" ]; then
    echo "Cleaning build directory..."
    rm -rf build
    echo "Build directory cleaned."
else
    echo "Building project..."
    cmake -B build -S .
    cd build
    make
    cd ..
fi