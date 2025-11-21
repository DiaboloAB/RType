from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, CMakeDeps
from conan.tools.files import copy
import os


class HoltzmanConan(ConanFile):
    name = "Holtzman"
    version = "0.1"
    settings = "os", "compiler", "build_type", "arch"

    generators = "CMakeDeps", "CMakeToolchain"

    options = {
        "shared": [True, False],
        "tests": [True, False],
    }
    default_options = {
        "shared": False,
        "tests": False,
    }

    exports_sources = (
        "CMakeLists.txt",
        "engine/*",
        "libs/*",
        "include/*",
        "src/*",
        "assets/*",
    )

    def requirements(self):
        self.requires("nlohmann_json/3.11.2")
        self.requires("asio/1.28.0")
        self.requires("lua/5.4.6")

        if self.options.tests:
            self.requires("gtest/1.14.0")

    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables["ASSETS_PATH"] = "assets/"
        tc.variables["TESTS"] = "ON" if self.options.tests else "OFF"

        # important for multi-dir projects
        tc.variables["CMAKE_POLICY_DEFAULT_CMP0091"] = "NEW"


        deps = CMakeDeps(self)

    def build(self):
        cmake = CMake(self)
        cmake.configure()   # will configure from the root CMakeLists.txt
        cmake.build()

        if self.options.tests:
            cmake.test()

    def package(self):
        copy(self, "*.hpp", src="include", dst=os.path.join(self.package_folder, "include"))
        copy(self, "*.h", src="include", dst=os.path.join(self.package_folder, "include"))
        copy(self, "*.a", src=".", dst=os.path.join(self.package_folder, "lib"), keep_path=False)
        copy(self, "*.so*", src=".", dst=os.path.join(self.package_folder, "lib"), keep_path=False)
        copy(self, "*.dll", src=".", dst=os.path.join(self.package_folder, "bin"), keep_path=False)
        copy(self, "*.dylib", src=".", dst=os.path.join(self.package_folder, "lib"), keep_path=False)

    def package_info(self):
        self.cpp_info.libs = ["Holtzman"]
