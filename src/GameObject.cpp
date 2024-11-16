#include <stdexcept>

#include <openge/ColorConstants.hpp>
#include <openge/GLBuffer.hpp>
#include <openge/GameObject.hpp>
#include <openge/Image.hpp>
#include <openge/Material.hpp>
#include <openge/Mesh.hpp>
#include <openge/RenderPipeline.hpp>
#include <openge/Transform.hpp>

namespace {

ge::Mesh::MeshData createCubeMeshData() {
    return {
        std::vector<ge::Mesh::Position> {
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

        std::vector<ge::Mesh::Normal> {
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

        std::vector<ge::Mesh::TextureCoordinate> {
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

        std::vector<ge::Mesh::Index> {
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

        ge::GLBuffer::UsagePattern::StaticDraw,

        ge::Mesh::Topology::Triangles
    };
}

ge::Mesh::MeshData createPrimitiveMeshData(
    ge::GameObject::Primitive primitive) {
    switch (primitive) {
        case ge::GameObject::Primitive::Cube:
            return createCubeMeshData();

        default:
            throw std::invalid_argument("Unsupported GameObject Primitive");
    }
}

std::shared_ptr<ge::Material> createPrimitiveMaterial() {
    using ge::RenderPipeline::Program;
    using ge::RenderPipeline::Uniform::Material::DIFFUSE_TEXTURE;
    using ge::RenderPipeline::Uniform::Material::DIFFUSE_TEXTURE_UNIT;
    using ge::RenderPipeline::Uniform::Material::SPECULAR_TEXTURE;
    using ge::RenderPipeline::Uniform::Material::SPECULAR_TEXTURE_UNIT;

    auto shaderProgram =
        ge::RenderPipeline::getShaderProgram(Program::Standard);

    ge::Image image(1, 1, ge::Image::Format::Format_RGBA8888);
    image.fill(ge::ColorConstants::WHITE);

    auto texture = std::make_shared<ge::GLTexture>(image);

    auto material = std::make_shared<ge::Material>(std::move(shaderProgram));
    material->addTexture(DIFFUSE_TEXTURE, DIFFUSE_TEXTURE_UNIT, texture);
    material->addTexture(SPECULAR_TEXTURE, SPECULAR_TEXTURE_UNIT, texture);

    return material;
}

}  // namespace

namespace ge {

GameObjectPtr GameObject::create() {
    auto gameObject = GameObjectPtr(new GameObject());
    gameObject->addComponent<Transform>();
    return gameObject;
}

GameObjectPtr GameObject::create(Primitive primitive) {
    auto gameObject = create();

    gameObject->addComponent<Mesh>(createPrimitiveMeshData(primitive),
                                   createPrimitiveMaterial());

    return gameObject;
}

void GameObject::render() {
    auto meshes = getComponents<Mesh>();
    for (auto &mesh : meshes) {
        mesh->render();
    }
}

void GameObject::update() {
    for (auto &componentFamily : components) {
        for (auto &component : componentFamily.second) {
            component->update();
        }
    }
}

}  // namespace ge
