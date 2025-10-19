from conan import ConanFile
from conan.tools.build import check_min_cppstd, can_run
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout, CMakeDeps
from conan.tools.scm import Git


class OpenGERecipe(ConanFile):
    name = "openge"
    package_type = "library"

    settings = "os", "compiler", "build_type", "arch"

    options = {
        "shared": [True, False],
        "fPIC": [True, False]
    }

    default_options = {
        "shared": False,
        "fPIC": True,
        "glad*:gl_profile": "core",
    }

    exports_sources = "CMakeLists.txt", \
        "src/*", "include/*", "platform/*", "shader/*", \
        "mock/*", "test/*"

    def set_version(self):
        git = Git(self, self.recipe_folder)
        tag = git.run('describe --tags')
        self.version = \
            '.'.join(tag.split('-')[:-1]) if '-' in tag else f"{tag}.0"

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
        self.tool_requires("cppcheck/2.16.0")
        self.tool_requires("doxygen/1.9.4")

    def requirements(self):
        self.requires("assimp/5.4.3")
        self.requires("glm/1.0.1", transitive_headers=True)
        self.requires("spdlog/1.16.0")

        if not self.settings.os == "Android":
            self.requires("glad/0.1.36", transitive_headers=True)
            self.requires("glfw/3.4", transitive_headers=True)
            self.requires("stb/cci.20230920")

        self.test_requires("gtest/[~1.14]")

    def layout(self):
        cmake_layout(self)
        if self.settings.os == "Android":
            self.cpp.source.includedirs += ["platform/android/include"]
        else:
            self.cpp.source.includedirs += ["platform/pc/include"]

    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()

        tc = CMakeToolchain(self)

        if not self.settings.os == "Android":
            tc.preprocessor_definitions["GLFW_INCLUDE_NONE"] = None

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
        else:
            self.cpp_info.defines.append("GLFW_INCLUDE_NONE")
