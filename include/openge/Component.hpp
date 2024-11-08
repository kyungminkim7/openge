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
    explicit Component(std::shared_ptr<GameObject> gameObject);

    virtual ~Component() = default;

    /**
     * Overridable behavior called once upon being added to a GameObject.
     */
    virtual void init();

    /**
     * Overridable behavior called every frame.
     */
    virtual void update();

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
