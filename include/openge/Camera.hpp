#pragma once

#include <glm/mat4x4.hpp>
#include <memory>
#include <openge/Component.hpp>

namespace ge {

class GameObject;

/**
 * Device through which the player views the world.
 */
class Camera : public Component {
 public:
  /**
   * Construct a camera.
   *
   * @param gameObject Game object this camera is attached to.
   * @param aspect Aspect ratio (width / height).
   * @param fieldOfView Vertical field of view in degrees.
   * @param nearClipPlane Distance to the nearest point of the view frustrum.
   * @param farClipPlane Distance to the furthest point of the view frustrum.
   */
  explicit Camera(std::shared_ptr<GameObject> gameObject, float aspect,
                  float fieldOfView = 60.0f, float nearClipPlane = 0.3f,
                  float farClipPlane = 1000.0f);

  /**
   * Gets the camera's projection matrix.
   *
   * @return Projection matrix.
   */
  glm::mat4 getProjectionMatrix() const;

  /**
   * Set the aspect ratio.
   *
   * @param aspect Aspect ratio (width / height).
   */
  void setAspect(float aspect);

 private:
  void updateProjectionMatrix();

  float aspect;
  float fieldOfView;  // Vertical field of view in radians
  float nearClipPlane;
  float farClipPlane;

  glm::mat4 projectionMatrix;
};

}  // namespace ge
