from conan import ConanFile
from conan.tools.build import check_max_cppstd, check_min_cppstd, can_run
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
        "src/*", "include/*", "platform/*", "shader/*"\
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
        self.requires("glm/1.0.1", transitive_headers=True)
        self.requires("lua/5.4.7", transitive_headers=True)

        if not self.settings.os == "Android":
            self.requires("qt/6.4.2", transitive_headers=True)

        self.test_requires("gtest/[~1.14]")

    def layout(self):
        cmake_layout(self)
        if self.settings.os == "Android":
            self.cpp.source.includedirs += ["platform/android/include"]
        else:
            self.cpp.source.includedirs += ["platform/qt/include"]

    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()
        tc = CMakeToolchain(self)
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

        if can_run(self):
            cmake.ctest()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = ["openge"]
        if self.settings.os == "Android":
            self.cpp_info.system_libs = ["GLESv3", "android",
                                         "jnigraphics", "log"]
