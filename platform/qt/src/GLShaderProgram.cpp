#include <utility>

#include <openge/Exception.hpp>
#include <openge/GLShaderProgram.hpp>

namespace ge {

void GLShaderProgram::addShader(std::shared_ptr<GLShader> shader) {
    if (!program.addShader(shader.get())) {
        throw BuildError(program.log().toStdString());
    }

    shaders.emplace_back(std::move(shader));
}

void GLShaderProgram::addShaderFromSourceFile(GLShader::ShaderType type,
                                              const char *source) {
    if (!program.addShaderFromSourceFile(type, source)) {
        throw BuildError(program.log().toStdString());
    }
}

void GLShaderProgram::link() {
    if (!program.link()) {
        throw BuildError(program.log().toStdString());
    }
}

void GLShaderProgram::bind() {
    if (!program.bind()) {
        throw BuildError(program.log().toStdString());
    }
}

void GLShaderProgram::release() {
    program.release();
}

void GLShaderProgram::enableAttributeArray(const char *name) {
    program.enableAttributeArray(name);
}

void GLShaderProgram::setAttributeBuffer(const char *name, GLenum type,
                                         int offset, int tupleSize,
                                         int stride) {
    program.setAttributeBuffer(name, type,
                               offset, tupleSize, stride);
}

void GLShaderProgram::setUniformValue(const char *name,
                                      float x, float y, float z, float w) {
    program.setUniformValue(name, x, y, z, w);
}

}  // namespace ge
