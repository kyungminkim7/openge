#include <spdlog/spdlog.h>

#include <fstream>
#include <iterator>
#include <string>

#include <openge/Exception.hpp>
#include <openge/GLShader.hpp>

namespace ge {

void GLShader::compileSourceFile(const char *filepath) {
    spdlog::info("Compiling shader: {}", filepath);

    std::ifstream fileStream(filepath);

    if (!fileStream.is_open()) {
        using namespace std::string_literals;
        throw BuildError("Failed to open shader file: "s + filepath);
    }

    const std::string source{
        std::istreambuf_iterator<char>(fileStream),
        std::istreambuf_iterator<char>()
    };

    compileSourceCode(source.c_str());
}

}  // namespace ge
