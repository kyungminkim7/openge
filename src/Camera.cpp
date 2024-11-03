#include <utility>

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/trigonometric.hpp>
#include <openge/Camera.hpp>

namespace ge {

Camera::Camera(std::shared_ptr<GameObject> gameObject,
               float aspect, float fieldOfView,
               float nearClipPlane, float farClipPlane) :
    Component(std::move(gameObject)),
    aspect(aspect),
    fieldOfView(glm::radians(fieldOfView)),
    nearClipPlane(nearClipPlane),
    farClipPlane(farClipPlane) {
    updateProjectionMatrix();
}

glm::mat4 Camera::getProjectionMatrix() const {
    return projectionMatrix;
}

void Camera::updateProjectionMatrix() {
    projectionMatrix = glm::perspective(fieldOfView, aspect,
                                        nearClipPlane, farClipPlane);
}

void Camera::setAspect(float aspect) {
    this->aspect = aspect;
    updateProjectionMatrix();
}

}  // namespace ge
