
#!/bin/bash


if [ "$1" == "clean" ]; then
    echo "Cleaning build directory..."
    rm -rf build
    echo "Build directory cleaned."
elif [ "$1" == "runtest" ]; then
    echo "Running tests..."
    cd build
    ctest
    cd ..
elif [ "$1" == "build" ]; then
    echo "Building project..."
    cmake -B build -S .
    cd build
    make
    cd ..
elif [ "$1" == "rebuild" ]; then
    echo "Rebuilding project..."
    ./tools.sh clean
    ./tools.sh build
elif [ "$1" == "run" ]; then
    echo "Running project..."
    cd build
    ./RType
    cd ..
elif [ "$1" == "help" ]; then
    echo "Usage: ./tools.sh [command]"
    echo "Commands:"
    echo "  clean: Clean build directory."
    echo "  build: Build project."
    echo "  rebuild: Rebuild project."
    echo "  runtest: Run tests."
    echo "  run: Run project."
else
    echo "Invalid command. Use './tools.sh help' to see available commands."
fi