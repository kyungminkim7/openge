#include <openge/GameObject.hpp>
#include <openge/Light.hpp>
#include <utility>

namespace ge {

Light::Light(std::shared_ptr<GameObject> gameObject)
    : Component(std::move(gameObject)), color(1.0f) {}

glm::vec3 Light::getColor() const { return color; }

void Light::setColor(const glm::vec3& color) { this->color = color; }

}  // namespace ge
