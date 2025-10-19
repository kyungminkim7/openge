#pragma once

#include <memory>

#include <openge/GLBuffer.hpp>
#include <openge/GLShaderProgram.hpp>
#include <openge/GLVertexArrayObject.hpp>

namespace ge {

/**
 * Wrapper around the entire scene that shows what the world looks like beyond
 * your geometry.
 */
class Skybox {
 public:
    /**
     * Construct a skybox from a set of images for each face.
     *
     * @param front Front face image filepath.
     * @param back Back face image filepath.
     * @param left Left face image filepath.
     * @param right Right face image filepath.
     * @param up Up face image filepath.
     * @param down Down face image filepath.
     */
    Skybox(const char *front, const char *back,
           const char *left, const char *right,
           const char *up, const char *down);

    ~Skybox();

    /**
     * Renders the skybox.
     */
    void render();

 private:
    void uploadFace(GLenum target, const char *filepath);

    void uploadTexture(const char *front, const char *back,
                       const char *left, const char *right,
                       const char *up, const char *down);

    void uploadVertexData();

    std::shared_ptr<GLShaderProgram> shaderProgram;

    GLVertexArrayObject vertexArray;
    GLBuffer vertexBuffer;

    unsigned int texture;
};

}  // namespace ge
