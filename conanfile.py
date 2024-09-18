from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMakeDeps
from conan.tools.system.package_manager import PacMan

class MyProjectConan(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"

    def requirements(self):
        self.requires("asio/1.31.0")
        self.requires("glfw/3.4")

    def system_requirements(self):
        pacman = PacMan(self)
        pacman.install(["libxcb", "libfontenc", "libice", "libsm", "libxaw", "libxcomposite", "libxcursor"], update=True, check=True)

    def build_requirements(self):
        self.tool_requires("cmake/3.22.6")


from conan import ConanFile

