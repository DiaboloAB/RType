<div style="text-align:center">
  <img src="https://shmups.wiki/images/thumb/6/64/R-Type_Logo.png/500px-R-Type_Logo.png" width="400" alt="logo"/>
</div>

**Welcome to the RType README! <br>
In this README you can access informations about many topics!**

# Building the Project

## Prerequisites

- **CMake** (3.10+)
- **Conan** (1.36+)

## Building on Linux

1. Open a terminal and navigate to your project directory.
```bash
cd path\to\your\project
```
2. Create a build directory:
```bash
mkdir build && cd build
```
3. Install dependencies:
```bash
conan install .. --output-folder=build/conan --build=missing
```
4. Configure with CMake:
```bash
cmake .. -DCMAKE_TOOLCHAIN_FILE=conan/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
```
5. Build the project:
```bash
cmake --build .
```


## Building on Windows

1. Open a terminal and navigate to your project directory.
```cmd
cd path\to\your\project
```
2. Create a build directory:
```cmd
mkdir build && cd build
```
3. Install dependencies:
```cmd
conan install .. --output-folder=build\conan --build=missing
```
4. Configure with CMake:
```cmd
cmake .. -DCMAKE_TOOLCHAIN_FILE=conan\conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
```
5. Build the project
```cmd
cmake --build . --config Release
```

## Customization

To build with SDL, use:
```bash
conan install .. -o graphics=SDL --output-folder=build/conan --build=missing
```

# General use
  - [Build & run the project](https://github.com/DiaboloAB/RType/wiki/Build-&-Run)
  - [Playing guide](https://github.com/DiaboloAB/RType/wiki/Playing-guide)

# Implementing your own features
  - [Animations](https://github.com/DiaboloAB/RType/wiki/Adding-animation-to-an-entity)
  - [Game](https://github.com/DiaboloAB/RType/wiki/How-to-create-a-game-%3F)

# Project specifications
  - [Scripting](https://github.com/DiaboloAB/RType/wiki/Introduction-to-Lua-Scripting-and-JSON-Parsing-in-Our-Game-Engine)
  - [Network](https://github.com/DiaboloAB/RType/wiki/Network)
  - [Graphic](https://github.com/DiaboloAB/RType/wiki/RenderSystemSFML-Documentation)