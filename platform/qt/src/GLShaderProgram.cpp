#include <QMatrix3x3>
#include <QMatrix4x4>
#include <QVector3D>
#include <utility>

#include <glm/gtc/type_ptr.hpp>
#include <openge/Exception.hpp>
#include <openge/GLShaderProgram.hpp>

namespace ge {

void GLShaderProgram::create() {
    if (!program.create()) {
        throw BuildError("Failed to create shader program object.");
    }
}

void GLShaderProgram::addShaderFromSourceCode(ge::GLShader::ShaderTypeBit type,
                                              const char *source) {
    if (!program.addShaderFromSourceCode(type, source)) {
        throw BuildError(program.log().toStdString());
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

void GLShaderProgram::setUniformValue(const char *name,
                                      const ge::Color &value) {
    program.setUniformValue(name, value);
}

void GLShaderProgram::setUniformValue(const char *name,
                                      const glm::vec3 &value) {
    program.setUniformValue(name,
                            QVector3D(value.x, value.y, value.z));
}

void GLShaderProgram::setUniformValue(const char *name,
                                      const glm::mat3 &value) {
    program.setUniformValue(name,
        QMatrix3x3(glm::value_ptr(value)).transposed());
}

void GLShaderProgram::setUniformValue(const char *name,
                                      const glm::mat4 &value) {
    program.setUniformValue(name,
        QMatrix4x4(glm::value_ptr(value)).transposed());
}

}  // namespace ge
