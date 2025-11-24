#pragma once

#include <cstddef>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <memory>
#include <openge/Component.hpp>
#include <openge/GLBuffer.hpp>
#include <openge/GLShaderProgram.hpp>
#include <openge/GLVertexArrayObject.hpp>
#include <vector>

namespace ge {

class GameObject;
class Material;

/**
 * Contains vertices and triangle arrays.
 *
 * Conceptually, all vertex data is stored in separate arrays of the same size.
 * For example, if you have a mesh of 100 Vertices, and want to have a position,
 * normal and two texture coordinates for each vertex, then the mesh should have
 * vertices, normals, and texture coordinate arrays, each being 100 in size.
 * Data for i-th vertex is at index "i" in each array.
 */
class Mesh : public Component {
 public:
  /**
   * Topology of Mesh faces.
   */
  enum class Topology { Triangles };

  /**
   * Index buffer type.
   */
  using Index = unsigned int;

  /**
   * Mesh normal type.
   */
  using Normal = glm::vec3;

  /**
   * Texture coordinate type.
   */
  using TextureCoordinate = glm::vec2;

  /**
   * Vertex position type.
   */
  using Position = glm::vec3;

  /**
   * Mesh data.
   */
  struct MeshData {
    /**
     * Vertex positions.
     */
    std::vector<Position> positions;

    /**
     * Vertex normals.
     */
    std::vector<Normal> normals;

    /**
     * Vertex texture coordinates.
     */
    std::vector<TextureCoordinate> textureCoordinates;

    /**
     * Element buffer elements.
     */
    std::vector<Index> indices;

    /**
     * Buffer usage pattern.
     */
    GLBuffer::UsagePattern usagePattern;

    /**
     * Mesh face topology.
     */
    Topology topology;
  };

  /**
   * Constructs a mesh.
   *
   * @param gameObject Game object this mesh is attached to.
   * @param meshData Mesh data.
   * @param material Mesh material.
   */
  Mesh(std::shared_ptr<GameObject> gameObject, const MeshData& meshData,
       std::shared_ptr<Material> material);

  /**
   * Gets the material of mesh.
   *
   * @return Mesh material.
   */
  std::shared_ptr<Material> getMaterial();

  /**
   * Renders the mesh.
   */
  void render();

 private:
  void setVertexAttributes(std::size_t positionsOffset,
                           std::size_t normalsOffset,
                           std::size_t textureCoordinatesOffset,
                           GLShaderProgram* shaderProgram);

  void uploadIndices(const std::vector<Index>& indices);

  void uploadMeshData(const MeshData& meshData);

  void uploadVertices(const MeshData& meshData, GLShaderProgram* shaderProgram);

  GLVertexArrayObject vertexArray;
  GLBuffer vertexBuffer;
  GLBuffer elementBuffer;
  GLenum renderMode;

  std::shared_ptr<Material> material;

  std::size_t numIndices = 0;
};

}  // namespace ge
