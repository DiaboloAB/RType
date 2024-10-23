from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMakeDeps

class MyProjectConan(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"

    def requirements(self):
        self.requires("asio/1.31.0")
        self.requires("lua/5.4.7")
        self.requires("nlohmann_json/3.11.3")
        self.requires("sdl/2.30.8")
        self.requires("sdl_ttf/2.22.0")
        self.requires("sdl_mixer/2.8.0")

    def build_requirements(self):
        self.tool_requires("cmake/3.22.6")


from conan import ConanFile

