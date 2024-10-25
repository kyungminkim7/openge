#include <utility>

#include <openge/Material.hpp>
#include <openge/Mesh.hpp>

namespace ge {

Mesh::Mesh(std::shared_ptr<GameObject> gameObject) :
    Component(std::move(gameObject)) {}

void Mesh::render() {
    if (material != nullptr) {
        auto shaderProgram = material->getShaderProgram();
        shaderProgram->bind();

        material->render();
    }
}

void Mesh::setMaterial(std::shared_ptr<Material> material) {
    this->material = std::move(material);
}

}  // namespace ge
