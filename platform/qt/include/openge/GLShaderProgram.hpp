#pragma once

#include <QOpenGLShaderProgram>
#include <type_traits>

#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <openge/Color.hpp>
#include <openge/GLShader.hpp>

namespace ge {

/**
 * Shader programs written in the OpenGL Shading Language (GLSL)
 * and in the OpenGL/ES Shading Language (GLSL/ES).
 */
class GLShaderProgram {
 public:
    /**
     * Create the shader program.
     *
     * @param BuildError Failed to create shader program.
     */
    void create();

    /**
     * Compiles source as a shader of the specified type and
     * adds it to this shader program.
     *
     * @param type Shader type to compile as.
     * @param source Shader source code.
     * @exception BuildError Failed to add shader.
     */
    void addShaderFromSourceCode(ge::GLShader::ShaderTypeBit type,
                                 const char *source);

    /**
     * Compiles source as a shader of the specified type and
     * adds it to this shader program.
     *
     * The file should be embedded using QRC in an assets directory
     * and only the relative filepath from assets should be given.
     *
     * @param type Shader type to compile as.
     * @param filepath Shader source code filepath.
     * @exception BuildError Failed to add shader.
     */
    void addShaderFromSourceFile(ge::GLShader::ShaderTypeBit type,
                                 const char *filepath);

    /**
     * Links the shaders added to the program.
     *
     * @exception BuildError Failed to link program.
     */
    void link();

    /**
     * Binds the shader program to the active OpenGL context
     * to make it the current shader program.
     *
     * @exception BuildError Failed to bind program.
     */
    void bind();

    /**
     * Releases the active shader program from the current OpenGL
     * context. This is equivalent to calling glUseProgram(0).
     */
    void release();

    /**
     * Enables the vertex array by name in this shader program.
     *
     * @param name Vertex array name.
     */
    void enableAttributeArray(const char *name);

    /**
     * Sets an array of vertex values on the attribute by name
     * in this shader program.
     *
     * @param name Vertex array name.
     * @param type Type of element in vertex array.
     * @param offset Start of values in currently bound vertex buffer.
     * @param tupleSize Number of components per vertex.
     * @param stride Number of bytes between vertices.
     */
    void setAttributeBuffer(const char *name, GLenum type, int offset,
                            int tupleSize, int stride = 0);

    /**
     * Sets the uniform value in the current context.
     *
     * @param name Uniform name.
     * @param value Uniform value.
     */
    template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    void setUniformValue(const char *name, T value);

    /**
     * Sets the uniform value in the current context.
     *
     * @param name Uniform name.
     * @param value Uniform value.
     */
    void setUniformValue(const char *name, const ge::Color &value);

    /**
     * Sets the uniform value in the current context.
     *
     * @param name Uniform name.
     * @param value Uniform value.
     */
    void setUniformValue(const char *name, const glm::vec3 &value);

    /**
     * Sets the uniform value in the current context.
     *
     * @param name Uniform name.
     * @param value Uniform value.
     */
    void setUniformValue(const char *name, const glm::mat3 &value);

    /**
     * Sets the uniform value in the current context.
     *
     * @param name Uniform name.
     * @param value Uniform value.
     */
    void setUniformValue(const char *name, const glm::mat4 &value);

    /**
     * Sets the uniform value in the current context.
     *
     * @param name Uniform name.
     * @param x
     * @param y
     * @param z
     */
    template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    void setUniformValue(const char *name, T x, T y, T z);

    /**
     * Sets the uniform value in the current context.
     *
     * @param name Uniform name.
     * @param x
     * @param y
     * @param z
     * @param w
     */
    template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    void setUniformValue(const char *name, T x, T y, T z, T w);

 private:
    QOpenGLShaderProgram program;
};

}  // namespace ge

#include <openge/GLShaderProgramImpl.hpp>
