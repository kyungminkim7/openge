#pragma once

#include <memory>

#include <openge/OpenGLFactory.hpp>

namespace ge {

/**
 * Factory for classes from the Qt OpenGL module.
 */
class QtOpenGLFactory : public OpenGLFactory {
 public:
    std::unique_ptr<Shader>
        createShader(Shader::ShaderType type) const override;
};

}  // namespace ge
