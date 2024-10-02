#pragma once

#include <QOpenGLTexture>

namespace ge {

/**
 * OpenGL textures.
 */
class GLTexture {
 public:
    /**
     * Texture filtering parameters.
     */
    using Filter = QOpenGLTexture::Filter;

    /**
     * Texture coordinate wrapping modes.
     */
    using WrapMode = QOpenGLTexture::WrapMode;

    /**
     * Creates an OpenGL texture object from an image file.
     *
     * The file should be embedded using QRC in an assets directory
     * and only the relative filepath from assets should be given.
     *
     * @note This creates the underlying OpenGL texture object
     *       and requires a valid current OpenGL context.
     *
     * @param filepath Image filepath to create a texture from.
     * @param generateMipMaps Generate chain of mipmaps.
     */
    explicit GLTexture(const char *filepath,
                       bool generateMipMaps = true);

    /**
     * Binds this texture to a texture unit ready for rendering.
     *
     * @param unit Texture unit to bind to.
     */
     void bind(unsigned int unit);

    /**
     * Sets the wrap/repeat mode for all texture dimensions.
     *
     * @param mode Wrap mode to set.
     */
    void setWrapMode(WrapMode mode);

    /**
     * Sets minification filter.
     *
     * @param filter Minification filter.
     */
    void setMinificationFilter(Filter filter);

    /**
     * Sets magnification filter.
     *
     * @param filter Magnification filter.
     */
    void setMagnificationFilter(Filter filter);

 private:
    QOpenGLTexture texture;
};

}  // namespace ge
