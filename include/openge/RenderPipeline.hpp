#pragma once

#include <memory>
#include <vector>

namespace ge {

class GLShaderProgram;

namespace RenderPipeline {
    namespace Attribute {
        extern const char *POSITION;
        extern const char *NORMAL;
        extern const char *TEXTURE_COORDINATE;
    }  // namespace Attribute

    namespace Uniform {
        extern const char *MODEL;
        extern const char *VIEW;
        extern const char *PROJECTION;

        namespace Material {
            extern const char *COLOR;
            extern const std::vector<const char *> TEXTURES;
        }  // namespace Material
    }  // namespace Uniform

    namespace Standard {
        /**
         * Provides a built-in standard shader program to render world objects.
         *
         * @return Standard shader program.
         */
        std::shared_ptr<GLShaderProgram> getShaderProgram();
    }  // namespace Standard

    /**
     * Destroys all built-in shader programs.
     */
    void destroy();
}  // namespace RenderPipeline

}  // namespace ge
