#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <numeric>
#include <stdexcept>
#include <string>

#include <assimp/Importer.hpp>
#include <glm/vec3.hpp>
#include <openge/AssimpIOSystem.hpp>
#include <openge/ColorConstants.hpp>
#include <openge/Exception.hpp>
#include <openge/GLBuffer.hpp>
#include <openge/GLTexture.hpp>
#include <openge/GameObject.hpp>
#include <openge/Image.hpp>
#include <openge/Material.hpp>
#include <openge/Mesh.hpp>
#include <openge/RenderPipeline.hpp>
#include <openge/Transform.hpp>

namespace {

using ge::RenderPipeline::Program;
using ge::RenderPipeline::Uniform::Material::DIFFUSE_TEXTURE;
using ge::RenderPipeline::Uniform::Material::DIFFUSE_TEXTURE_UNIT;
using ge::RenderPipeline::Uniform::Material::SPECULAR_TEXTURE;
using ge::RenderPipeline::Uniform::Material::SPECULAR_TEXTURE_UNIT;

std::unordered_map<std::string, std::weak_ptr<ge::GLTexture>> textureCache;

std::shared_ptr<ge::GLTexture> createBlankTexture() {
    ge::Image image(1, 1, ge::Image::Format::Format_RGBA8888);
    image.fill(ge::ColorConstants::WHITE);
    return std::make_shared<ge::GLTexture>(image);
}

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
    auto shaderProgram =
        ge::RenderPipeline::getShaderProgram(Program::Standard);

    auto texture = createBlankTexture();

    auto material = std::make_shared<ge::Material>(std::move(shaderProgram));
    material->addTexture(DIFFUSE_TEXTURE, DIFFUSE_TEXTURE_UNIT, texture);
    material->addTexture(SPECULAR_TEXTURE, SPECULAR_TEXTURE_UNIT, texture);

    return material;
}

unsigned int getNumIndices(const aiMesh *mesh) {
    return std::accumulate(mesh->mFaces,
                           mesh->mFaces + mesh->mNumFaces,
                           0u,
                           [](auto sum, const auto &face){
                               return sum + face.mNumIndices;
                           });
}

ge::Mesh::MeshData createMeshData(const aiMesh *mesh) {
    ge::Mesh::MeshData data;
    data.positions.reserve(mesh->mNumVertices);
    data.normals.reserve(mesh->mNumVertices);
    data.textureCoordinates.reserve(mesh->mNumVertices);
    data.indices.reserve(getNumIndices(mesh));
    data.usagePattern = ge::GLBuffer::UsagePattern::StaticDraw;
    data.topology = ge::Mesh::Topology::Triangles;

    // Load vertex data.
    for (auto i = 0u; i < mesh->mNumVertices; ++i) {
        const auto &position = mesh->mVertices[i];
        data.positions.emplace_back(position.x, position.y, position.z);

        const auto &normal = mesh->mNormals[i];
        data.normals.emplace_back(normal.x, normal.y, normal.z);

        mesh->mTextureCoords[0] ?
            data.textureCoordinates.emplace_back(mesh->mTextureCoords[0][i].x,
                                                 mesh->mTextureCoords[0][i].y) :
            data.textureCoordinates.emplace_back(0.0f, 0.0f);
    }

    // Load indices.
    for (auto face = mesh->mFaces;
         face < mesh->mFaces + mesh->mNumFaces;
         ++face) {
        data.indices.insert(data.indices.cend(),
                            face->mIndices,
                            face->mIndices + face->mNumIndices);
    }

    return data;
}

std::shared_ptr<ge::GLTexture> createTexture(const aiScene *scene,
                                             const aiMesh *mesh,
                                             const std::filesystem::path &dir,
                                             aiTextureType type) {
    const auto material = scene->mMaterials[mesh->mMaterialIndex];

    if (material->GetTextureCount(type) == 0) {
        return createBlankTexture();
    }

    aiString filename;
    material->GetTexture(type, 0, &filename);
    const std::string filepath(dir / filename.C_Str());

    auto texture = textureCache[filepath].lock();
    if (texture) {
        return texture;
    }

    auto textureDeleter = [filepath](auto *texture){
        textureCache.erase(filepath);
        delete texture;
    };

    texture = std::shared_ptr<ge::GLTexture>(
        new ge::GLTexture(ge::Image(filepath.c_str())),
        textureDeleter);

    texture->setWrapMode(ge::GLTexture::WrapMode::Repeat);
    texture->setMinificationFilter(ge::GLTexture::Filter::LinearMipMapLinear);
    texture->setMagnificationFilter(ge::GLTexture::Filter::Linear);

    textureCache[filepath] = texture;

    return texture;
}

std::shared_ptr<ge::Material> createMaterial(const aiScene *scene,
                                             const aiMesh *mesh,
                                             const std::filesystem::path &dir) {
    auto shaderProgram =
        ge::RenderPipeline::getShaderProgram(Program::Standard);

    auto diffuseTexture = createTexture(scene, mesh, dir,
                                        aiTextureType_DIFFUSE);

    auto specularTexture = createTexture(scene, mesh, dir,
                                         aiTextureType_SPECULAR);

    auto material = std::make_shared<ge::Material>(std::move(shaderProgram));

    material->addTexture(DIFFUSE_TEXTURE, DIFFUSE_TEXTURE_UNIT,
                         std::move(diffuseTexture));

    material->addTexture(SPECULAR_TEXTURE, SPECULAR_TEXTURE_UNIT,
                         std::move(specularTexture));

    return material;
}

void addNode(ge::GameObject *gameObject,
             const aiScene *scene,
             const aiNode *node,
             const std::filesystem::path &dir) {
    for (auto i = node->mMeshes;
         i < node->mMeshes + node->mNumMeshes;
         ++i) {
        auto mesh = scene->mMeshes[*i];
        gameObject->addComponent<ge::Mesh>(createMeshData(mesh),
                                           createMaterial(scene, mesh, dir));
    }

    for (auto child = node->mChildren;
         child < node->mChildren + node->mNumChildren;
         ++child) {
        addNode(gameObject, scene, *child, dir);
    }
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

GameObjectPtr GameObject::create(const std::filesystem::path &model) {
    Assimp::Importer importer;
    importer.SetIOHandler(AssimpIOSystem::create());

    const auto flags = aiProcess_Triangulate | aiProcess_FlipUVs;
    const auto scene = importer.ReadFile(model, flags);

    if (scene == nullptr ||
        scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE ||
        scene->mRootNode == nullptr) {
        throw LoadError("Failed to load model from: " + model.string());
    }

    auto gameObject = create();
    addNode(gameObject.get(), scene, scene->mRootNode, model.parent_path());
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
