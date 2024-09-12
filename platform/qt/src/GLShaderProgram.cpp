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
                                              const std::string &source) {
    if (!program.addShaderFromSourceFile(type, source.c_str())) {
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

void GLShaderProgram::enableAttributeArray(int location) {
    program.enableAttributeArray(location);
}

void GLShaderProgram::setAttributeBuffer(int location, GLenum type,
                                         int offset, int tupleSize,
                                         int stride) {
    program.setAttributeBuffer(location, type,
                               offset, tupleSize, stride);
}

}  // namespace ge
