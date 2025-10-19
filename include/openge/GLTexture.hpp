#pragma once

#include <openge/OpenGL.hpp>

namespace ge {

class Image;

/**
 * OpenGL textures.
 */
class GLTexture {
 public:
    /**
     * Options for controlling mipmap generation;
     */
    enum class MipMapGeneration {
        GenerateMipMaps,
        DontGenerateMipMaps
    };

    /**
     * Texture target.
     */
    enum class Target: GLenum {
        Target2D = GL_TEXTURE_2D,
        Target2DArray = GL_TEXTURE_2D_ARRAY,
        Target3D = GL_TEXTURE_3D,
        TargetCubeMap = GL_TEXTURE_CUBE_MAP,
        Target2DMultisample = GL_TEXTURE_2D_MULTISAMPLE,
        Target2DMultisampleArray = GL_TEXTURE_2D_MULTISAMPLE_ARRAY,
        TargetBuffer = GL_TEXTURE_BUFFER
    };

    /**
     * Texture filtering parameters.
     */
    enum class Filter: GLint {
        Nearest = GL_NEAREST,
        Linear = GL_LINEAR,
        NearestMipMapNearest = GL_NEAREST_MIPMAP_NEAREST,
        NearestMipMapLinear = GL_NEAREST_MIPMAP_LINEAR,
        LinearMipMapNearest = GL_LINEAR_MIPMAP_NEAREST,
        LinearMipMapLinear = GL_LINEAR_MIPMAP_LINEAR
    };

    /**
     * Texture coordinate wrapping modes.
     */
    enum class WrapMode: GLint {
        Repeat = GL_REPEAT,
        MirroredRepeat = GL_MIRRORED_REPEAT,
        ClampToEdge = GL_CLAMP_TO_EDGE,
        ClampToBorder = GL_CLAMP_TO_BORDER
    };

    /**
     * Creates an OpenGL texture object from an image.
     *
     * @note This creates the underlying OpenGL texture object
     *       and requires a valid current OpenGL context.
     *
     * @param image Image to create a texture from.
     * @param genMipMaps Generate chain of mipmaps.
     */
    explicit GLTexture(const Image &image,
        MipMapGeneration genMipMaps = MipMapGeneration::GenerateMipMaps);

    ~GLTexture();

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
    GLenum target;
    GLuint texture;
};

}  // namespace ge
