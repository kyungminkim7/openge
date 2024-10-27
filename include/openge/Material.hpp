#pragma once

#include <cstddef>
#include <memory>
#include <vector>

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
     * Appends the given texture. Textures are rendered in order.
     *
     * @param texture Texture to append.
     */
    void addTexture(TexturePtr texture);

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
     * Replaces the texture at the location of the index.
     *
     * @param texture Texture to set as.
     * @param index Index of texture to replace.
     */
    void setTexture(TexturePtr texture, std::size_t index = 0);

 private:
    std::shared_ptr<GLShaderProgram> shaderProgram;
    Color color;
    std::vector<TexturePtr> textures;
};

}  // namespace ge
