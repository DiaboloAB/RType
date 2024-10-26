@echo off
REM Detect the Conan profile
conan profile detect --force

REM Install Conan dependencies
conan install . --output-folder=build/conan --build=missing -c "tools.system.package_manager:mode=install" -c "tools.system.package_manager:sudo=true"

REM Change directory to the build folder
cd build

REM Run CMake with Visual Studio generator and Conan toolchain file
cmake .. -G "Visual Studio 17 2022" -DCMAKE_TOOLCHAIN_FILE="conan/conan_toolchain.cmake" -DCMAKE_POLICY_DEFAULT_CMP0091=NEW

REM Build the project in Release mode
cmake --build . --config Release
