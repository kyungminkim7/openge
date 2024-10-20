#pragma once

#include <memory>

namespace ge {

struct GameObject;

/**
 * Base class for everything attached to a GameObject.
 */
class Component {
 public:
    /**
     * Construct a component.
     *
     * @param gameObject Game object this component is attached to.
     */
    explicit Component(const std::shared_ptr<GameObject> &gameObject);

 protected:
    /**
     * Get the game object this component is attached to.
     *
     * @return Game object this component is attached to.
     */
    std::shared_ptr<GameObject> getGameObject();

 private:
    std::weak_ptr<GameObject> gameObject;
};

}  // namespace ge
