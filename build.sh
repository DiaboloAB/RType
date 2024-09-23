conan profile detect --force
conan install . --output-folder=build --build=missing -c "tools.system.package_manager:mode=install" -c "tools.system.package_manager:sudo=true"
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
cmake --build .
