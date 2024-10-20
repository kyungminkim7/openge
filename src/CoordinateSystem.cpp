#include <openge/CoordinateSystem.hpp>

#include <glm/vec3.hpp>

namespace ge {

const glm::vec3 CoordinateSystem::FORWARD { 1.0f, 0.0f, 0.0f };
const glm::vec3 CoordinateSystem::BACK = -FORWARD;

const glm::vec3 CoordinateSystem::LEFT { 0.0f, 1.0f, 0.0f };
const glm::vec3 CoordinateSystem::RIGHT = -LEFT;

const glm::vec3 CoordinateSystem::UP { 0.0f, 0.0f, 1.0f };
const glm::vec3 CoordinateSystem::DOWN = -UP;

const glm::vec3 CoordinateSystem::ORIGIN { 0.0f, 0.0f, 0.0f };

}  // namespace ge
