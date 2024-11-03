#pragma once

#include <memory>
#include <vector>

namespace ge {

class GLShaderProgram;
class GameObject;

}  // namespace ge

namespace ge::RenderPipeline {

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

/**
 * Built-in shader program.
 */
enum class Program {
    Standard
};

/**
 * Destroys all built-in shader programs.
 */
void destroy();

/**
 * Provides a built-in standard shader program to render world objects.
 *
 * @param pipeline Built-in shader program type.
 * @return Standard shader program.
 */
std::shared_ptr<GLShaderProgram> getShaderProgram(Program program);

/**
 * Uploads projection and view matrices to active shader programs.
 *
 * @param camera Camera.
 */
void uploadCameraMatrices(GameObject *camera);

}  // namespace ge::RenderPipeline
