#include <array>
#include <filesystem>
#include <iterator>
#include <sstream>
#include <string>
#include <system_error>
#include <type_traits>
#include <vector>

#include <openge/Asset.hpp>
#include <openge/Exception.hpp>
#include <openge/GLShader.hpp>
#include <openge/Log.hpp>

namespace ge {

GLShader::GLShader(ShaderTypeBit type) :
    shader(glCreateShader(
        static_cast<std::underlying_type_t<ShaderTypeBit>>(type))) {}

GLShader::~GLShader() {
    glDeleteShader(shader);
}

void GLShader::compileSourceCode(const char *source) {
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        std::array<char, 512> log;
        GLsizei length;
        glGetShaderInfoLog(shader, log.size(), &length, log.data());

        std::string logStr(log.cbegin(),
                           std::next(log.cbegin(), length));
        throw BuildError(logStr);
    }
}

void GLShader::compileSourceFile(const char *filepath) {
    using namespace std::string_literals;

    Asset file(filepath, Asset::Mode::Buffer);
    std::vector<char> sourceCode(file.getLength());
    const auto bytesRead = file.read(sourceCode.data(), sourceCode.size());

    if (bytesRead != sourceCode.size()) {
        const auto errorCode = std::make_error_code(std::errc::file_too_large);

        std::stringstream errorMessage;
        errorMessage << "Failed to read " << filepath;

        throw std::filesystem::filesystem_error(errorMessage.str(), errorCode);
    }

    std::string sourceCodeStr(sourceCode.cbegin(), sourceCode.cend());

    Log::info("Compiling shader: "s + filepath);
    compileSourceCode(sourceCodeStr.c_str());
}

GLuint GLShader::shaderId() const {
    return shader;
}

}  // namespace ge
