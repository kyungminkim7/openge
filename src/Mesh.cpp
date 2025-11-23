#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>

#include <glm/ext/matrix_transform.hpp>
#include <glm/mat3x3.hpp>
#include <glm/matrix.hpp>
#include <openge/GameObject.hpp>
#include <openge/Material.hpp>
#include <openge/Mesh.hpp>
#include <openge/RenderPipeline.hpp>
#include <openge/Transform.hpp>

namespace {

constexpr auto POSITION_STRIDE =
    ge::Mesh::Position::length() *
    sizeof(ge::Mesh::Position::value_type);

constexpr auto NORMAL_STRIDE =
    ge::Mesh::Normal::length() *
    sizeof(ge::Mesh::Normal::value_type);

constexpr auto TEXTURE_COORDINATE_STRIDE =
    ge::Mesh::TextureCoordinate::length() *
    sizeof(ge::Mesh::TextureCoordinate::value_type);

GLenum getRenderMode(ge::Mesh::Topology topology) {
    switch (topology) {
        case ge::Mesh::Topology::Triangles:
            return GL_TRIANGLES;

        default:
            throw std::invalid_argument("Unsupported render mode");
    }
}

}  // namespace

namespace ge {

Mesh::Mesh(std::shared_ptr<GameObject> gameObject,
           const MeshData &meshData,
           std::shared_ptr<Material> material) :
    Component(std::move(gameObject)),
    vertexArray(),
    vertexBuffer(ge::GLBuffer::Type::VertexBuffer),
    elementBuffer(ge::GLBuffer::Type::IndexBuffer),
    renderMode(getRenderMode(meshData.topology)),
    material(std::move(material)) {
    vertexArray.create();

    vertexBuffer.create();
    vertexBuffer.setUsagePattern(meshData.usagePattern);

    elementBuffer.create();
    elementBuffer.setUsagePattern(meshData.usagePattern);

    uploadMeshData(meshData);
}

std::shared_ptr<Material> Mesh::getMaterial() {
    return material;
}

void Mesh::render() {
    auto shaderProgram = material->getShaderProgram();

    shaderProgram->bind();
    vertexArray.bind();
    material->bind();

    const auto transform = getGameObject()->getComponent<ge::Transform>();

    const auto model = glm::scale(transform->getLocalToWorldMatrix(),
                                  transform->getScale());

    const auto normal = glm::mat3(glm::transpose(glm::inverse(model)));

    shaderProgram->setUniformValue(ge::RenderPipeline::Uniform::MODEL, model);
    shaderProgram->setUniformValue(ge::RenderPipeline::Uniform::NORMAL, normal);

    glDrawElements(renderMode, numIndices, GL_UNSIGNED_INT, nullptr);
}

void Mesh::setVertexAttributes(std::size_t positionsOffset,
                               std::size_t normalsOffset,
                               std::size_t textureCoordinatesOffset,
                               GLShaderProgram *shaderProgram) {
    // Enable attributes
    shaderProgram->enableAttributeArray(
        ge::RenderPipeline::Attribute::POSITION);

    shaderProgram->enableAttributeArray(
        ge::RenderPipeline::Attribute::NORMAL);

    shaderProgram->enableAttributeArray(
        ge::RenderPipeline::Attribute::TEXTURE_COORDINATE);

    // Set attributes
    shaderProgram->setAttributeBuffer(
        ge::RenderPipeline::Attribute::POSITION,
        GL_FLOAT, positionsOffset, Position::length(),
        POSITION_STRIDE);

    shaderProgram->setAttributeBuffer(
        ge::RenderPipeline::Attribute::NORMAL,
        GL_FLOAT, normalsOffset, Normal::length(), NORMAL_STRIDE);

    shaderProgram->setAttributeBuffer(
        ge::RenderPipeline::Attribute::TEXTURE_COORDINATE,
        GL_FLOAT, textureCoordinatesOffset, TextureCoordinate::length(),
        TEXTURE_COORDINATE_STRIDE);
}

void Mesh::uploadIndices(const std::vector<Index> &indices) {
    elementBuffer.allocate(indices.data(), indices.size() * sizeof(Index));
    numIndices = indices.size();
}

void Mesh::uploadMeshData(const MeshData &meshData) {
    auto shaderProgram = material->getShaderProgram();

    shaderProgram->bind();
    vertexArray.bind();
    vertexBuffer.bind();
    elementBuffer.bind();

    uploadVertices(meshData, shaderProgram.get());
    uploadIndices(meshData.indices);
}

void Mesh::uploadVertices(const MeshData &meshData,
                          GLShaderProgram *shaderProgram) {
    const auto positionsSize = meshData.positions.size() * POSITION_STRIDE;
    const auto normalsSize = meshData.normals.size() * NORMAL_STRIDE;
    const auto textureCoordinatesSize = meshData.textureCoordinates.size() *
                                        TEXTURE_COORDINATE_STRIDE;

    const auto meshDataSize = positionsSize +
                              normalsSize +
                              textureCoordinatesSize;

    const auto positionsOffset = 0;
    const auto normalsOffset = positionsOffset + positionsSize;
    const auto textureCoordinatesOffset = normalsOffset + normalsSize;

    vertexBuffer.allocate(meshDataSize);

    vertexBuffer.write(positionsOffset,
                       meshData.positions.data(),
                       positionsSize);

    vertexBuffer.write(normalsOffset,
                       meshData.normals.data(),
                       normalsSize);

    vertexBuffer.write(textureCoordinatesOffset,
                       meshData.textureCoordinates.data(),
                       textureCoordinatesSize);

    setVertexAttributes(positionsOffset,
                        normalsOffset,
                        textureCoordinatesOffset,
                        shaderProgram);
}

}  // namespace ge
