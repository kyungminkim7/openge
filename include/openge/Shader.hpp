#pragma once

#include <string_view>

namespace ge {

/**
 * Interface for compiling OpenGL shaders.
 */
class Shader {
 public:
    /**
     * Type of OpenGL shader.
     */
    enum class ShaderType {
        Vertex,
        Fragment,
        Geometry,
        TessellationControl,
        TessellationEvaluation,
        Compute
    };

    virtual ~Shader() = default;
};

}  // namespace ge
