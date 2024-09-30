#!/bin/bash

usage() {
    echo "Usage: $0 <command> [path]"
    echo "Commands:"
    echo "  clean: Clean build directory."
    echo "  build: Build project."
    echo "  rebuild: Rebuild project."
    echo "  runtest: Run tests."
    echo "  run: Run project."
    echo "  check-clang: Check code formatting in the specified directory."
    echo "       path: the directory to check for format issues (e.g., src or include)"
    echo "  fix-clang: Fix code formatting in the specified directory."
    exit 1
}

if [ $# -lt 1 ]; then
    usage
fi

COMMAND=$1

if [ "$COMMAND" == "runtest" ]; then
    echo "Running tests..."
    cd build
    ./test_basic
    ./libs/ecs/test_ecs
    ./engine/test_engine
    cd ..
elif [ "$COMMAND" == "build" ]; then
    conan profile detect --force
    conan install . --output-folder=build/conan --build=missing -c "tools.system.package_manager:mode=install" -c "tools.system.package_manager:sudo=true"
    cd build
    cmake .. -DCMAKE_TOOLCHAIN_FILE=conan/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
    cmake --build .
elif [ "$COMMAND" == "pack" ]; then
    conan profile detect --force
    conan install . --output-folder=build/conan --build=missing -c "tools.system.package_manager:mode=install" -c "tools.system.package_manager:sudo=true"
    cd build
    cmake .. -DCMAKE_TOOLCHAIN_FILE=conan/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
    cpack --config CPackConfig.cmake
elif [ "$COMMAND" == "clean" ]; then
    echo "Cleaning project..."
    rm -rf build
    rm RType
    rm CMakeUserPresets.json
elif [ "$COMMAND" == "rebuild" ]; then
    echo "Rebuilding project..."
    $0 clean
    $0 build
elif [ "$COMMAND" == "run" ]; then
    echo "Running project..."
    cd build
    ./RType
    cd ..
elif [ "$COMMAND" == "check-clang" ]; then
    if [ $# -ne 2 ]; then
        usage
    fi

    DIRECTORY=$2

    if [ ! -d "$DIRECTORY" ]; then
        echo "Directory $DIRECTORY does not exist."
        exit 1
    fi

    IGNORE_LIST=(
        "$DIRECTORY/build/*"
        "*CMakeFiles*"
        "*tests/*"
    )

    ERROR_FLAG=0

    FIND_CMD="find \"$DIRECTORY\" -type f \( -name '*.cpp' -o -name '*.hpp' \)"
    for IGNORE in "${IGNORE_LIST[@]}"; do
        FIND_CMD+=" -not -path \"$IGNORE\""
    done

    FILES=$(eval $FIND_CMD)

    for FILE in $FILES; do
        clang-format --dry-run --Werror "$FILE"
        if [ $? -ne 0 ]; then
            echo "::error file=$FILE::File $FILE is not formatted correctly."
            ERROR_FLAG=1
        fi
    done

    exit $ERROR_FLAG
elif [ "$COMMAND" == "fix-clang" ]; then
    if [ $# -ne 2 ]; then
        usage
    fi

    DIRECTORY=$2

    if [ ! -d "$DIRECTORY" ]; then
        echo "Directory $DIRECTORY does not exist."
        exit 1
    fi

    IGNORE_LIST=(
        "$DIRECTORY/build/*"
        "*CMakeFiles*"
        "*tests/*"
    )

    FIND_CMD="find \"$DIRECTORY\" -type f \( -name '*.cpp' -o -name '*.hpp' \)"
    for IGNORE in "${IGNORE_LIST[@]}"; do
        FIND_CMD+=" -not -path \"$IGNORE\""
    done

    FILES=$(eval $FIND_CMD)

    for FILE in $FILES; do
        clang-format -i "$FILE"
    done

elif [ "$COMMAND" == "help" ]; then
    usage
else
    echo "Unknown command: $COMMAND"
    usage
fi