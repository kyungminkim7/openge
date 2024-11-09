#include <utility>

#include <openge/Component.hpp>

namespace ge {

Component::Component(std::weak_ptr<GameObject> gameObject) :
    gameObject(std::move(gameObject)) {}

std::shared_ptr<GameObject> Component::getGameObject() {
    return gameObject.lock();
}

void Component::init() {}

void Component::update() {}

}  // namespace ge
