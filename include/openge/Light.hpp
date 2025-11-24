#pragma once

#include <glm/vec3.hpp>
#include <memory>

namespace ge {

class GameObject;

/**
 * Lighting.
 */
class Light : public Component {
 public:
  /**
   * Constructs a light.
   *
   * @param gameObject Game object this light is attached to.
   */
  explicit Light(std::shared_ptr<GameObject> gameObject);

  /**
   * Returns the color of the light.
   *
   * @return Light color.
   */
  glm::vec3 getColor() const;

  /**
   * Sets the color of the light.
   *
   * @param color Light color.
   */
  void setColor(const glm::vec3& color);

 private:
  glm::vec3 color;
};

}  // namespace ge
