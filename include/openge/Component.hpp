#pragma once

#include <functional>
#include <memory>
#include <vector>

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
  explicit Component(std::weak_ptr<GameObject> gameObject);

  virtual ~Component();

  /**
   * Add an input event listener for this component and registers automatic
   * cleanup upon component destruction.
   */
  template <typename Event, typename Listener>
  void addInputListener(Listener listener);

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
  using CleanUp = std::function<void()>;

  std::weak_ptr<GameObject> gameObject;

  std::vector<CleanUp> cleanUp;
};

}  // namespace ge

#include <openge/impl/Component.hpp>
