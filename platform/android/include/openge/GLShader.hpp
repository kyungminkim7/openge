#pragma once

#include <GLES3/gl32.h>

namespace ge {

/**
 * Allows OpenGL shaders to be compiled.
 */
class GLShader {
 public:
    /**
     * Shader type.
     */
    enum class ShaderTypeBit : GLenum {
        Vertex = GL_VERTEX_SHADER,
        Fragment = GL_FRAGMENT_SHADER,
        Geometry = GL_GEOMETRY_SHADER,
        TessellationControl = GL_TESS_CONTROL_SHADER,
        TessellationEvaluation = GL_TESS_EVALUATION_SHADER,
        Compute = GL_COMPUTE_SHADER
    };

    /**
     * Constructs a new shader object.
     *
     * @param type Shader type.
     */
    explicit GLShader(ShaderTypeBit type);

    ~GLShader();

    /**
     * Sets the source code for this shader and compiles it.
     *
     * @param source Source code.
     * @exception BuildError Failed to compile shader.
     */
    void compileSourceCode(const char *source);

    /**
     * Sets the source code for this shader and compiles it.
     *
     * @param filepath Source code filepath.
     * @exception BuildError Failed to compile shader.
     */
    void compileSourceFile(const char *filepath);

    /**
     * Returns the OpenGL identifier associated with this shader.
     *
     * @return Shader ID.
     */
    GLuint shaderId() const;

 private:
    GLuint shader;
};

}  // namespace ge
