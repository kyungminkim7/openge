#pragma once

#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <openge/GLShader.hpp>
#include <openge/OpenGL.hpp>

namespace ge {

/**
 * Shader programs written in the OpenGL Shading Language (GLSL)
 * and in the OpenGL/ES Shading Language (GLSL/ES).
 */
class GLShaderProgram {
 public:
  ~GLShaderProgram();

  /**
   * Compiles source as a shader of the specified type and
   * adds it to this shader program.
   *
   * @param type Shader type to compile as.
   * @param source Shader source code.
   * @exception BuildError Failed to add shader.
   */
  void addShaderFromSourceCode(ge::GLShader::ShaderTypeBit type,
                               const char* source);

  /**
   * Compiles source as a shader of the specified type and
   * adds it to this shader program.
   *
   * @param type Shader type to compile as.
   * @param filepath Shader source code filepath.
   * @exception BuildError Failed to add shader.
   */
  void addShaderFromSourceFile(ge::GLShader::ShaderTypeBit type,
                               const char* filepath);

  /**
   * Returns the location of the attribute within this shader
   * program's parameter list.
   *
   * @param name Attribute name.
   * @return Attribute location.
   * @exception std::invalid_argument Name is not an attribute.
   */
  int attributeLocation(const char* name) const;

  /**
   * Binds the shader program to the active OpenGL context
   * to make it the current shader program.
   */
  void bind();

  /**
   * Create the shader program.
   *
   * @param BuildError Failed to create shader program.
   */
  void create();

  /**
   * Enables the vertex array by name in this shader program.
   *
   * @param name Vertex array name.
   */
  void enableAttributeArray(const char* name);

  /**
   * Links the shaders added to the program.
   *
   * @exception BuildError Failed to link program.
   */
  void link();

  /**
   * Releases the active shader program from the current OpenGL
   * context. This is equivalent to calling glUseProgram(0).
   */
  void release();

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
  void setAttributeBuffer(const char* name, GLenum type, int offset,
                          int tupleSize, int stride = 0);

  /**
   * Sets the uniform value in the current context.
   *
   * @param name Uniform name.
   * @param value Uniform value.
   */
  void setUniformValue(const char* name, GLint value);

  /**
   * Sets the uniform value in the current context.
   *
   * @param name Uniform name.
   * @param value Uniform value.
   */
  void setUniformValue(const char* name, GLfloat value);

  /**
   * Sets the uniform value in the current context.
   *
   * @param name Uniform name.
   * @param x X value.
   * @param y Y value.
   */
  void setUniformValue(const char* name, GLfloat x, GLfloat y);

  /**
   * Sets the uniform value in the current context.
   *
   * @param name Uniform name.
   * @param x X value.
   * @param y Y value.
   * @param z Z value.
   */
  void setUniformValue(const char* name, GLfloat x, GLfloat y, GLfloat z);

  /**
   * Sets the uniform value in the current context.
   *
   * @param name Uniform name.
   * @param x X value.
   * @param y Y value.
   * @param z Z value.
   * @param w W value.
   */
  void setUniformValue(const char* name, GLfloat x, GLfloat y, GLfloat z,
                       GLfloat w);

  /**
   * Sets the uniform value in the current context.
   *
   * @param name Uniform name.
   * @param value Uniform value.
   */
  void setUniformValue(const char* name, const glm::vec3& value);

  /**
   * Sets the uniform value in the current context.
   *
   * @param name Uniform name.
   * @param value Uniform value.
   */
  void setUniformValue(const char* name, const glm::mat3& value);

  /**
   * Sets the uniform value in the current context.
   *
   * @param name Uniform name.
   * @param value Uniform value.
   */
  void setUniformValue(const char* name, const glm::mat4& value);

  /**
   * Returns the location of the uniform variable within this
   * shader program's parameter list.
   *
   * @param name Uniform variable name.
   * @return Uniform location.
   */
  int uniformLocation(const char* name) const;

 private:
  GLuint program;
};

}  // namespace ge
