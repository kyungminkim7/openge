#include <utility>

#include <glm/ext/quaternion_transform.hpp>
#include <glm/geometric.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/mat3x3.hpp>
#include <openge/Transform.hpp>

namespace ge {

Transform::Transform(std::shared_ptr<GameObject> gameObject) :
    Component(std::move(gameObject)),
    scale{1.0f}, position{ 0.0f }, rotation{ glm::identity<glm::quat>() }  {}

glm::vec3 Transform::getForward() const {
    return glm::mat3_cast(rotation)[0];
}

glm::vec3 Transform::getLeft() const {
    return glm::mat3_cast(rotation)[1];
}

glm::vec3 Transform::getUp() const {
    return glm::mat3_cast(rotation)[2];
}

glm::vec3 Transform::getPosition() const {
    return position;
}

glm::quat Transform::getRotation() const {
    return rotation;
}

glm::vec3 Transform::getScale() const {
    return scale;
}

glm::vec3 Transform::inverseTransformDirection(const glm::vec3 &direction) {
    return direction * rotation;
}

void Transform::lookAt(const glm::vec3 &worldPosition,
                       const glm::vec3 &worldUp) {
    const auto x = glm::normalize(worldPosition - getPosition());
    const auto y = glm::normalize(glm::cross(worldUp, x));
    const auto z = glm::normalize(glm::cross(x, y));
    rotation = glm::quat_cast(glm::mat3(x, y, z));
}

void Transform::rotate(const glm::vec3 &axis, float radians, Space relativeTo) {
    rotation = glm::rotate(rotation, radians,
        relativeTo == Space::Self ? axis : inverseTransformDirection(axis));
}

void Transform::setPosition(const glm::vec3 &position) {
    this->position = position;
}

void Transform::setRotation(const glm::quat &rotation) {
    this->rotation = rotation;
}

void Transform::setScale(const glm::vec3 &scale) {
    this->scale = scale;
}

glm::vec3 Transform::transformDirection(const glm::vec3 &direction) {
    return rotation * direction;
}

void Transform::translate(const glm::vec3 &translate, Space relativeTo) {
    this->position += relativeTo == Space::Self ?
        transformDirection(translate) : translate;
}

}  // namespace ge
