from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMakeDeps

class MyProjectConan(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"

    def requirements(self):
        self.requires("asio/1.31.0")
        self.requires("sfml/2.6.1")
        self.requires("lua/5.4.7")
        self.requires("nlohmann_json/3.11.3")

    def build_requirements(self):
        self.tool_requires("cmake/3.22.6")


from conan import ConanFile

