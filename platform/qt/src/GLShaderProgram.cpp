#include <utility>

#include <openge/Exception.hpp>
#include <openge/GLShaderProgram.hpp>

namespace ge {

void GLShaderProgram::create() {
    if (!program.create()) {
        throw BuildError("Failed to create shader program object.");
    }
}

void GLShaderProgram::addShaderFromSourceFile(ge::GLShader::ShaderTypeBit type,
                                              const char *filepath) {
    if (!program.addShaderFromSourceFile(type, filepath)) {
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

}  // namespace ge
