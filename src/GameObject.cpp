#include <stdexcept>

#include <openge/ColorConstants.hpp>
#include <openge/GameObject.hpp>
#include <openge/Image.hpp>
#include <openge/Material.hpp>
#include <openge/Mesh.hpp>
#include <openge/RenderPipeline.hpp>
#include <openge/Transform.hpp>

namespace {

ge::Mesh::MeshData createCubeMeshData() {
    return {
        // positions
        std::vector<glm::vec3> {
            // back face
            {-0.5f, -0.5f, -0.5f},  // bottom-left
            { 0.5f,  0.5f, -0.5f},  // top-right
            { 0.5f, -0.5f, -0.5f},  // bottom-right
            {-0.5f,  0.5f, -0.5f},  // top-left

            // front face
            {-0.5f, -0.5f,  0.5f},  // bottom-left
            { 0.5f, -0.5f,  0.5f},  // bottom-right
            { 0.5f,  0.5f,  0.5f},  // top-right
            {-0.5f,  0.5f,  0.5f},  // top-left

            // left face
            {-0.5f,  0.5f,  0.5f},  // top-right
            {-0.5f,  0.5f, -0.5f},  // top-left
            {-0.5f, -0.5f, -0.5f},  // bottom-left
            {-0.5f, -0.5f,  0.5f},  // bottom-right

            // right face
            { 0.5f,  0.5f,  0.5f},  // top-left
            { 0.5f, -0.5f, -0.5f},  // bottom-right
            { 0.5f,  0.5f, -0.5f},  // top-right
            { 0.5f, -0.5f,  0.5f},  // bottom-left

            // bottom face
            {-0.5f, -0.5f, -0.5f},  // top-right
            { 0.5f, -0.5f, -0.5f},  // top-left
            { 0.5f, -0.5f,  0.5f},  // bottom-left
            {-0.5f, -0.5f,  0.5f},  // bottom-right

            // top face
            {-0.5f,  0.5f, -0.5f},  // top-left
            { 0.5f,  0.5f , 0.5f},  // bottom-right
            { 0.5f,  0.5f, -0.5f},  // top-right
            {-0.5f,  0.5f,  0.5f}   // bottom-left
        },

        // normals
        std::vector<glm::vec3> {
            // back face
            { 0.0f,  0.0f, -1.0f},  // bottom-left
            { 0.0f,  0.0f, -1.0f},  // top-right
            { 0.0f,  0.0f, -1.0f},  // bottom-right
            { 0.0f,  0.0f, -1.0f},  // top-left

            // front face
            { 0.0f,  0.0f,  1.0f},  // bottom-left
            { 0.0f,  0.0f,  1.0f},  // bottom-right
            { 0.0f,  0.0f,  1.0f},  // top-right
            { 0.0f,  0.0f,  1.0f},  // top-left

            // left face
            { -1.0f,  0.0f,  0.0f},  // top-right
            { -1.0f,  0.0f,  0.0f},  // top-left
            { -1.0f,  0.0f,  0.0f},  // bottom-left
            { -1.0f,  0.0f,  0.0f},  // bottom-right

            // right face
            { 1.0f,  0.0f,  0.0f},  // top-left
            { 1.0f,  0.0f,  0.0f},  // bottom-right
            { 1.0f,  0.0f,  0.0f},  // top-right
            { 1.0f,  0.0f,  0.0f},  // bottom-left

            // bottom face
            { 0.0f, -1.0f,  0.0f},  // top-right
            { 0.0f, -1.0f,  0.0f},  // top-left
            { 0.0f, -1.0f,  0.0f},  // bottom-left
            { 0.0f, -1.0f,  0.0f},  // bottom-right

            // top face
            { 0.0f,  1.0f,  0.0f},  // top-left
            { 0.0f,  1.0f,  0.0f},  // bottom-right
            { 0.0f,  1.0f,  0.0f},  // top-right
            { 0.0f,  1.0f,  0.0f}   // bottom-left
        },

        // texture coordinates
        std::vector<glm::vec2> {
            // back face
            {0.0f, 0.0f},  // bottom-left
            {1.0f, 1.0f},  // top-right
            {1.0f, 0.0f},  // bottom-right
            {0.0f, 1.0f},  // top-left

            // front face
            {0.0f, 0.0f},  // bottom-left
            {1.0f, 0.0f},  // bottom-right
            {1.0f, 1.0f},  // top-right
            {0.0f, 1.0f},  // top-left

            // left face
            {1.0f, 0.0f},  // top-right
            {1.0f, 1.0f},  // top-left
            {0.0f, 1.0f},  // bottom-left
            {0.0f, 0.0f},  // bottom-right

            // right face
            {1.0f, 0.0f},  // top-left
            {0.0f, 1.0f},  // bottom-right
            {1.0f, 1.0f},  // top-right
            {0.0f, 0.0f},  // bottom-left

            // bottom face
            {0.0f, 1.0f},  // top-right
            {1.0f, 1.0f},  // top-left
            {1.0f, 0.0f},  // bottom-left
            {0.0f, 0.0f},  // bottom-right

            // top face
            {0.0f, 1.0f},  // top-left
            {1.0f, 0.0f},  // bottom-right
            {1.0f, 1.0f},  // top-right
            {0.0f, 0.0f}   // bottom-left
        },

        // indices
        std::vector<unsigned int> {
            // back face
            0u, 1u, 2u,
            1u, 0u, 3u,

            // front face
            4u, 5u, 6u,
            6u, 7u, 4u,

            // left face
            8u, 9u, 10u,
            10u, 11u, 8u,

            // right face
            12u, 13u, 14u,
            13u, 12u, 15u,

            // bottom face
            16u, 17u, 18u,
            18u, 19u, 16u,

            // top face
            20u, 21u, 22u,
            21u, 20u, 23u
        },

        ge::Mesh::Topology::Triangles
    };
}

ge::Mesh::MeshData createMeshData(ge::GameObject::PrimitiveType type) {
    switch (type) {
        case ge::GameObject::PrimitiveType::Cube:
            return createCubeMeshData();

        default:
            throw std::invalid_argument("Unsupported GameObject PrimitiveType");
    }
}

}  // namespace

namespace ge {

GameObjectPtr GameObject::create() {
    auto gameObject = GameObjectPtr(new GameObject());
    gameObject->addComponent<Transform>();
    return gameObject;
}

GameObjectPtr GameObject::createPrimitive(PrimitiveType type) {
    auto gameObject = create();

    auto shaderProgram = ge::RenderPipeline::Standard::getShaderProgram();

    ge::Image image(1, 1, ge::Image::Format::Format_RGBA8888);
    image.fill(ge::ColorConstants::WHITE);

    auto texture = std::make_shared<ge::GLTexture>(image);

    auto material = std::make_shared<ge::Material>(std::move(shaderProgram));
    material->addTexture(std::move(texture));

    auto mesh = gameObject->addComponent<ge::Mesh>(createMeshData(type),
                                                   std::move(material));

    return gameObject;
}

void GameObject::render() {
    auto meshes = getComponents<Mesh>();
    for (auto &mesh : meshes) {
        mesh->render();
    }
}

}  // namespace ge
