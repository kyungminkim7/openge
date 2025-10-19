#include <openge/Component.hpp>

namespace ge {

Component::Component(std::weak_ptr<GameObject> gameObject) :
    gameObject(std::move(gameObject)), cleanUp{} {}

Component::~Component() {
    for (const auto &cleanupFunc : cleanUp) {
        cleanupFunc();
    }
}

std::shared_ptr<GameObject> Component::getGameObject() {
    return gameObject.lock();
}

void Component::init() {}

void Component::update() {}

}  // namespace ge
