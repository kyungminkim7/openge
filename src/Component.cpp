#include <openge/Component.hpp>

namespace ge {

Component::Component(const std::shared_ptr<GameObject> &gameObject) :
    gameObject(gameObject) {}

std::shared_ptr<GameObject> Component::getGameObject() {
    return gameObject.lock();
}

}  // namespace ge
