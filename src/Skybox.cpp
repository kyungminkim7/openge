#include <array>

#include <glm/vec3.hpp>
#include <openge/GLTexture.hpp>
#include <openge/Image.hpp>
#include <openge/Material.hpp>
#include <openge/RenderPipeline.hpp>
#include <openge/Skybox.hpp>

using Position = glm::vec3;

namespace {

constexpr std::array<Position, 36> POSITIONS {
    glm::vec3{-1.0f,  1.0f, -1.0f},
    glm::vec3{-1.0f, -1.0f, -1.0f},
    glm::vec3{ 1.0f, -1.0f, -1.0f},
    glm::vec3{ 1.0f, -1.0f, -1.0f},
    glm::vec3{ 1.0f,  1.0f, -1.0f},
    glm::vec3{-1.0f,  1.0f, -1.0f},

    glm::vec3{-1.0f, -1.0f,  1.0f},
    glm::vec3{-1.0f, -1.0f, -1.0f},
    glm::vec3{-1.0f,  1.0f, -1.0f},
    glm::vec3{-1.0f,  1.0f, -1.0f},
    glm::vec3{-1.0f,  1.0f,  1.0f},
    glm::vec3{-1.0f, -1.0f,  1.0f},

    glm::vec3{ 1.0f, -1.0f, -1.0f},
    glm::vec3{ 1.0f, -1.0f,  1.0f},
    glm::vec3{ 1.0f,  1.0f,  1.0f},
    glm::vec3{ 1.0f,  1.0f,  1.0f},
    glm::vec3{ 1.0f,  1.0f, -1.0f},
    glm::vec3{ 1.0f, -1.0f, -1.0f},

    glm::vec3{-1.0f, -1.0f,  1.0f},
    glm::vec3{-1.0f,  1.0f,  1.0f},
    glm::vec3{ 1.0f,  1.0f,  1.0f},
    glm::vec3{ 1.0f,  1.0f,  1.0f},
    glm::vec3{ 1.0f, -1.0f,  1.0f},
    glm::vec3{-1.0f, -1.0f,  1.0f},

    glm::vec3{-1.0f,  1.0f, -1.0f},
    glm::vec3{ 1.0f,  1.0f, -1.0f},
    glm::vec3{ 1.0f,  1.0f,  1.0f},
    glm::vec3{ 1.0f,  1.0f,  1.0f},
    glm::vec3{-1.0f,  1.0f,  1.0f},
    glm::vec3{-1.0f,  1.0f, -1.0f},

    glm::vec3{-1.0f, -1.0f, -1.0f},
    glm::vec3{-1.0f, -1.0f,  1.0f},
    glm::vec3{ 1.0f, -1.0f, -1.0f},
    glm::vec3{ 1.0f, -1.0f, -1.0f},
    glm::vec3{-1.0f, -1.0f,  1.0f},
    glm::vec3{ 1.0f, -1.0f,  1.0f}
};

}  // namespace

namespace ge {

Skybox::Skybox(const char *front, const char *back,
               const char *left, const char *right,
               const char *up, const char *down) :
    shaderProgram(RenderPipeline::getShaderProgram(
                    RenderPipeline::Program::Skybox)),
    vertexArray(),
    vertexBuffer(GLBuffer::Type::VertexBuffer) {
    shaderProgram->bind();
    uploadVertexData();
    uploadTexture(front, back, left, right, up, down);
}

Skybox::~Skybox() {
    glDeleteTextures(1, &texture);
}

void Skybox::uploadFace(GLenum target, const char *filepath) {
    const auto image =
        Image(filepath).convertToFormat(Image::Format::Format_RGBA8888);

    glTexImage2D(target, 0, GL_RGBA, image.width(), image.height(), 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, image.bits());
}

void Skybox::uploadTexture(const char *front, const char *back,
                           const char *left, const char *right,
                           const char *up, const char *down) {
    glActiveTexture(GL_TEXTURE0 + RenderPipeline::Uniform::SKYBOX_TEXTURE_UNIT);

    shaderProgram->setUniformValue(
        RenderPipeline::Uniform::SKYBOX_TEXTURE,
        RenderPipeline::Uniform::SKYBOX_TEXTURE_UNIT);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

    uploadFace(GL_TEXTURE_CUBE_MAP_POSITIVE_X, front);
    uploadFace(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, back);
    uploadFace(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, left);
    uploadFace(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, right);
    uploadFace(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, up);
    uploadFace(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, down);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

void Skybox::uploadVertexData() {
    constexpr auto positionStride = Position::length() *
                                    sizeof(Position::value_type);

    vertexArray.create();
    vertexBuffer.create();
    vertexBuffer.setUsagePattern(GLBuffer::UsagePattern::StaticDraw);

    vertexArray.bind();
    vertexBuffer.bind();

    vertexBuffer.allocate(POSITIONS.data(),
                          POSITIONS.size() * positionStride);

    shaderProgram->enableAttributeArray(RenderPipeline::Attribute::POSITION);

    shaderProgram->setAttributeBuffer(RenderPipeline::Attribute::POSITION,
                                      GL_FLOAT, 0, Position::length(),
                                      positionStride);
}

void Skybox::render() {
    shaderProgram->bind();

    vertexArray.bind();

    glActiveTexture(GL_TEXTURE0 + RenderPipeline::Uniform::SKYBOX_TEXTURE_UNIT);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

    glDrawArrays(GL_TRIANGLES, 0, POSITIONS.size());
}

}  // namespace ge
