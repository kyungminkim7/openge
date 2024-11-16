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
extern const char *NORMAL;

extern const char *VIEW_POSITION;

namespace Material {
extern const char *DIFFUSE_TEXTURE;
extern const int DIFFUSE_TEXTURE_UNIT;

extern const char *SPECULAR_TEXTURE;
extern const int SPECULAR_TEXTURE_UNIT;

extern const char *SHINE;

extern const char *COLOR;
}  // namespace Material

namespace Light {
extern const char *AMBIENT;
}  // namespace Light

namespace DirectionalLight {
extern const char * COUNT;
extern const std::vector<const char *> DIRECTION;
extern const std::vector<const char *> COLOR;
}  // namespace DirectionalLight

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
 * Uploads camera data to shader programs.
 *
 * @param camera Camera.
 */
void uploadCamera(GameObject *camera);

}  // namespace ge::RenderPipeline
