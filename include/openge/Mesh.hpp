#pragma once

#include <memory>

#include <openge/Component.hpp>

namespace ge {

class GameObject;

/**
 * Contains vertices and triangle arrays.
 */
class Mesh : public Component {
 public:
    /**
     * Constructs a mesh.
     */
    explicit Mesh(const std::shared_ptr<GameObject> &gameObject);
};

}  // namespace ge
