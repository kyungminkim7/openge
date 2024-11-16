#pragma once

#include <cstddef>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>

#include <openge/Color.hpp>
#include <openge/GLShaderProgram.hpp>
#include <openge/GLTexture.hpp>

namespace ge {

/**
 * Describes the appearance of surfaces.
 */
class Material {
 public:
    /**
     * Texture smart pointer.
     */
    using TexturePtr = std::shared_ptr<GLTexture>;

    /**
     * Constructs a material.
     *
     * @param shaderProgram Shader program to use for rendering.
     */
    explicit Material(std::shared_ptr<GLShaderProgram> shaderProgram);

    /**
     * Adds the given texture.
     *
     * @param name Texture name.
     * @param unit Texture unit.
     * @param texture Texture to append.
     */
    void addTexture(const std::string &name, int unit, TexturePtr texture);

    /**
     * Gets the shader program used by the material.
     *
     * @return Shader program.
     */
    std::shared_ptr<GLShaderProgram> getShaderProgram();

    /**
     * Binds the material for rendering.
     */
    void bind();

    /**
     * Sets the color of the material.
     *
     * @param color Material color.
     */
    void setColor(const Color &color);

    /**
     * Sets the specular lighting shine component of the material.
     *
     * @param shine Material shine.
     */
    void setShine(float shine);

 private:
    std::shared_ptr<GLShaderProgram> shaderProgram;

    Color color;
    float shine;

    std::unordered_map<std::string, std::pair<int, TexturePtr>> textures;
};

}  // namespace ge
