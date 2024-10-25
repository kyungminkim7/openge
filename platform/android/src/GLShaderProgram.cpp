#include <array>
#include <iterator>
#include <stdexcept>
#include <string>

#include <glm/gtc/type_ptr.hpp>
#include <openge/Exception.hpp>
#include <openge/GLShaderProgram.hpp>

namespace ge {

GLShaderProgram::~GLShaderProgram() {
    glDeleteProgram(program);
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

void GLShaderProgram::bind() {
    glUseProgram(program);
}

void GLShaderProgram::create() {
    program = glCreateProgram();

    if (program == 0) {
        throw BuildError("Failed to create shader program object.");
    }
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

void GLShaderProgram::release() {
    glUseProgram(0);
}

void GLShaderProgram::setAttributeBuffer(const char *name, GLenum type,
                                         int offset, int tupleSize,
                                         int stride) {
    glVertexAttribPointer(attributeLocation(name), tupleSize,
                          type, GL_FALSE, stride,
                          reinterpret_cast<void *>(offset));
}

void GLShaderProgram::setUniformValue(const char *name, GLint value) {
    glUniform1i(uniformLocation(name), value);
}

void GLShaderProgram::setUniformValue(const char *name,
                                      GLfloat x, GLfloat y, GLfloat z) {
    glUniform3f(uniformLocation(name), x, y, z);
}

void GLShaderProgram::setUniformValue(const char *name,
                                      GLfloat x, GLfloat y, GLfloat z,
                                      GLfloat w) {
    glUniform4f(uniformLocation(name), x, y, z, w);
}

void GLShaderProgram::setUniformValue(const char *name,
                                      const glm::mat4 &value) {
    glUniformMatrix4fv(uniformLocation(name), 1, GL_FALSE,
                       glm::value_ptr(value));
}

int GLShaderProgram::uniformLocation(const char *name) const {
    using namespace std::string_literals;

    const auto location = glGetUniformLocation(program, name);

    if (location == -1) {
        throw std::invalid_argument(name + " is an invalid uniform"s);
    }

    return location;
}

}  // namespace ge
