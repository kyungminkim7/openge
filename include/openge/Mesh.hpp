#pragma once

#include <memory>

#include <openge/Component.hpp>

namespace ge {

class GameObject;
class Material;

/**
 * Contains vertices and triangle arrays.
 */
class Mesh : public Component {
 public:
    /**
     * Constructs a mesh.
     *
     * @param gameObject Game object this transform is attached to.
     */
    explicit Mesh(std::shared_ptr<GameObject> gameObject);

    /**
     * Renders the mesh.
     */
    void render();

    /**
     * Sets the material of the mesh.
     *
     * @param material Material to set.
     */
    void setMaterial(std::shared_ptr<Material> material);

 private:
    std::shared_ptr<Material> material;
};

}  // namespace ge
