#pragma once

#include <QOpenGLShader>

#include <openge/Shader.hpp>

namespace ge {

/**
 * QOpenGLShader wrapper.
 */
class QtShader : public Shader {
 public:
    /**
     * Constructs a new QtShader object of the specified type.
     * 
     * @param type Shader type.
     */
    explicit QtShader(Shader::ShaderType type);
};

}  // namespace ge
