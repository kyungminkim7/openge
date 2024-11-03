#include <openge/Component.hpp>

namespace ge {

Component::Component(std::shared_ptr<GameObject> gameObject) :
    gameObject(gameObject) {}

std::shared_ptr<GameObject> Component::getGameObject() {
    return gameObject.lock();
}

void Component::update() {}

}  // namespace ge
