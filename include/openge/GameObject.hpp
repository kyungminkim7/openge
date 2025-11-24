#pragma once

#include <filesystem>
#include <memory>
#include <typeindex>
#include <unordered_map>
#include <vector>

namespace ge {

class GameObject;
class Component;

using GameObjectPtr = std::shared_ptr<GameObject>;

/**
 * Base class for all entities in Scenes.
 */
class GameObject : public std::enable_shared_from_this<GameObject> {
 public:
  /**
   * Primitive types of game objects that can be created.
   */
  enum class Primitive { Cube };

  /**
   * Factory function for creating a game object.
   *
   * @return Game object.
   */
  static GameObjectPtr create();

  /**
   * Creates a game object of the specified primitive type.
   *
   * @param primitive Primitive type of game object to create.
   * @return Constructed primitive game object.
   */
  static GameObjectPtr create(Primitive primitive);

  /**
   * Creates a game object from a 3D model file.
   *
   * @param model 3D model filepath.
   */
  static GameObjectPtr create(const std::filesystem::path& model);

  /**
   * Add a component to the game object.
   *
   * @return Added component.
   */
  template <typename T, typename... Args>
  std::shared_ptr<T> addComponent(Args&&... args);

  /**
   * Gets the first attached component of a specific type.
   *
   * @return Attached component.
   */
  template <typename T>
  std::shared_ptr<T> getComponent();

  /**
   * Gets all attached components of a specific type.
   *
   * @return Attached components, empty container
   *         if no components of the type are attached.
   */
  template <typename T>
  std::vector<std::shared_ptr<T>> getComponents();

  /**
   * Renders the game object.
   */
  void render();

  /**
   * Updates the game object and all attached components.
   */
  void update();

 private:
  GameObject() = default;

  template <typename T>
  std::type_index getComponentTypeIndex() const;

  using ComponentPtr = std::shared_ptr<Component>;
  using ComponentPtrs = std::vector<ComponentPtr>;
  std::unordered_map<std::type_index, ComponentPtrs> components;
};

}  // namespace ge

#include <openge/impl/GameObject.hpp>
