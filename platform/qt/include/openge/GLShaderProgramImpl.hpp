#pragma once

namespace ge {

template<typename T, typename>
void GLShaderProgram::setUniformValue(const char *name, T value) {
    program.setUniformValue(name, value);
}

template<typename T, typename>
void GLShaderProgram::setUniformValue(const char *name,
                                      T x, T y, T z) {
    program.setUniformValue(name, x, y, z);
}

template<typename T, typename>
void GLShaderProgram::setUniformValue(const char *name,
                                      T x, T y, T z, T w) {
    program.setUniformValue(name, x, y, z, w);
}

}  // namespace ge
