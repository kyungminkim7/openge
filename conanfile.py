from conan import ConanFile
from conan.tools.build import check_max_cppstd, check_min_cppstd
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout, CMakeDeps


class OpenGERecipe(ConanFile):
    name = "openge"
    version = "1.0"
    package_type = "library"

    # Binary configuration
    settings = "os", "compiler", "build_type", "arch"

    options = {
        "shared": [True, False],
        "fPIC": [True, False]
    }

    default_options = {
        "shared": False,
        "fPIC": True,
        "qt*:shared": True
    }

    # Sources are located in the same place as this recipe, copy them to the recipe
    exports_sources = "CMakeLists.txt", \
        "src/*", "include/*", "platform/*", \
        "mock/*", "test/*"

    def validate(self):
        check_min_cppstd(self, "17")

    def config_options(self):
        if self.settings.os == "Windows":
            self.options.rm_safe("fPIC")

    def configure(self):
        if self.options.shared:
            self.options.rm_safe("fPIC")

    def build_requirements(self):
        self.tool_requires("cmake/[>=3.23]")
        self.tool_requires("cppcheck/2.14.1")
        self.tool_requires("doxygen/1.9.4")

    def requirements(self):
        self.requires("lua/5.4.7")
        if not self.settings.os == "Android":
            self.requires("qt/6.4.2")

        self.test_requires("gtest/[~1.14]")

    def layout(self):
        cmake_layout(self)

    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()
        tc = CMakeToolchain(self)
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
        cmake.ctest()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = ["openge"]
