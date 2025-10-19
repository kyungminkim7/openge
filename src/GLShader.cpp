#include <array>
#include <iterator>
#include <string>
#include <type_traits>

#include <openge/Exception.hpp>
#include <openge/GLShader.hpp>

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

GLuint GLShader::shaderId() const {
    return shader;
}

}  // namespace ge
