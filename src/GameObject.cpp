#include <openge/GameObject.hpp>
#include <openge/Transform.hpp>

namespace ge {

GameObjectPtr GameObject::create() {
    const auto gameObject = GameObjectPtr(new GameObject());
    gameObject->addComponent(std::make_shared<Transform>(gameObject));
    return gameObject;
}

}  // namespace ge
