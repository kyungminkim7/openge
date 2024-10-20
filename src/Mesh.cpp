#include <openge/Mesh.hpp>

namespace ge {

Mesh::Mesh(const std::shared_ptr<GameObject> &gameObject) :
    Component(gameObject) {}

}  // namespace ge
