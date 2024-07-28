#include <openge/QtOpenGLFactory.hpp>

#include <openge/QtShader.hpp>

namespace ge {

std::unique_ptr<Shader>
    QtOpenGLFactory::createShader(Shader::ShaderType type) const {
    return std::make_unique<QtShader>(type);
}

}  // namespace ge
