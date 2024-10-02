#include <array>
#include <iterator>
#include <stdexcept>
#include <string>

#include <openge/Exception.hpp>
#include <openge/GLShaderProgram.hpp>

namespace ge {

GLShaderProgram::~GLShaderProgram() {
    glDeleteProgram(program);
}

void GLShaderProgram::create() {
    program = glCreateProgram();

    if (program == 0) {
        throw BuildError("Failed to create shader program object.");
    }
}

void GLShaderProgram::addShaderFromSourceCode(ge::GLShader::ShaderTypeBit type,
                                              const char *source) {
    GLShader shader(type);
    shader.compileSourceCode(source);
    glAttachShader(program, shader.shaderId());
}

void GLShaderProgram::addShaderFromSourceFile(ge::GLShader::ShaderTypeBit type,
                                              const char *filepath) {
    GLShader shader(type);
    shader.compileSourceFile(filepath);
    glAttachShader(program, shader.shaderId());
}

void GLShaderProgram::link() {
    glLinkProgram(program);

    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);

    if (!success) {
        std::array<char, 512> log;
        GLsizei length;
        glGetProgramInfoLog(program, log.size(), &length, log.data());

        std::string logStr(log.cbegin(),
                           std::next(log.cbegin(), length));
        throw BuildError(logStr);
    }
}

void GLShaderProgram::bind() {
    glUseProgram(program);
}

void GLShaderProgram::release() {
    glUseProgram(0);
}

int GLShaderProgram::attributeLocation(const char *name) const {
    using namespace std::string_literals;

    const auto location = glGetAttribLocation(program, name);

    if (location == -1) {
        throw std::invalid_argument(name + " is an invalid attribute"s);
    }

    return location;
}

void GLShaderProgram::enableAttributeArray(const char *name) {
    glEnableVertexAttribArray(attributeLocation(name));
}

void GLShaderProgram::setAttributeBuffer(const char *name, GLenum type,
                                         int offset, int tupleSize,
                                         int stride) {
    glVertexAttribPointer(attributeLocation(name), tupleSize,
                          type, GL_FALSE, stride,
                          reinterpret_cast<void *>(offset));
}

int GLShaderProgram::uniformLocation(const char *name) const {
    using namespace std::string_literals;

    const auto location = glGetUniformLocation(program, name);

    if (location == -1) {
        throw std::invalid_argument(name + " is an invalid uniform"s);
    }

    return location;
}

void GLShaderProgram::setUniformValue(const char *name, GLint value) {
    glUniform1i(uniformLocation(name), value);
}

}  // namespace ge
