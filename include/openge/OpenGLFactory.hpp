#pragma once

#include <memory>

#include <openge/Shader.hpp>

namespace ge {

/**
 * Abstract Factory for OpenGL functionality.
 */
class OpenGLFactory {
 public:
    virtual ~OpenGLFactory() = default;

    /**
     * Creates a Shader.
     * 
     * @param type Shader type.
     */
    virtual std::unique_ptr<Shader>
        createShader(Shader::ShaderType type) const = 0;
};

}  // namespace ge
