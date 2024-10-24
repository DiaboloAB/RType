from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMakeDeps

class MyProjectConan(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"

    options = {
        "graphics": ["SFML", "SDL", "OFF"]
    }
    default_options = {
        "graphics": "SFML"
    }

    def requirements(self):
        self.requires("asio/1.31.0")
        self.requires("lua/5.4.7")
        self.requires("nlohmann_json/3.11.3")

        # Conditionally include SDL dependencies based on the graphics option
        if self.options.graphics == "SDL":
            self.requires("sdl_ttf/2.22.0")
            self.requires("sdl_mixer/2.8.0")
        elif self.options.graphics == "SFML":
            self.requires("sfml/2.6.1")

    def configure(self):
        # Override specific dependencies if needed
        if self.options.graphics == "SDL":
            self.requires("sdl/2.28.5", override=True)
            self.requires("flac/1.4.2", override=True)

    def build_requirements(self):
        self.tool_requires("cmake/3.22.6")


from conan import ConanFile

