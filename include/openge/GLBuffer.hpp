#pragma once

#include <openge/OpenGL.hpp>

namespace ge {

/**
 * Manages OpenGL buffer objects.
 */
class GLBuffer {
 public:
    /**
     * Type of OpenGL buffer to create.
     */
    enum class Type: GLenum {
        VertexBuffer = GL_ARRAY_BUFFER,
        IndexBuffer = GL_ELEMENT_ARRAY_BUFFER,
        PixelPackBuffer = GL_PIXEL_PACK_BUFFER,
        PixelUnpackBuffer = GL_PIXEL_UNPACK_BUFFER
    };

    /**
     * Buffer usage pattern.
     */
    enum class UsagePattern: GLenum {
        StreamDraw = GL_STREAM_DRAW,
        StreamRead = GL_STREAM_READ,
        StreamCopy = GL_STREAM_COPY,
        StaticDraw = GL_STATIC_DRAW,
        StaticRead = GL_STATIC_READ,
        StaticCopy = GL_STATIC_COPY,
        DynamicDraw = GL_DYNAMIC_DRAW,
        DynamicRead = GL_DYNAMIC_READ,
        DynamicCopy = GL_DYNAMIC_COPY
    };

    /**
     * Constructs a new buffer object of type.
     *
     * @note The actual buffer object in the OpenGL server is not
     *       created until create() is called.
     * 
     * @param type OpenGL buffer type to create.
     */
    explicit GLBuffer(Type type);

    ~GLBuffer();

    /**
     * Creates the buffer object.
     */
    void create();

    /**
     * Sets buffer object usage pattern.
     *
     * @param usage Usage pattern.
     */
    void setUsagePattern(UsagePattern usage);

    /**
     * Binds the buffer associated with this object to
     * the current OpenGL context.
     */
    void bind();

    /**
     * Allocates space to the buffer.
     *
     * @param count Bytes of space to allocate.
     */
    void allocate(int count);

    /**
     * Allocates space to the buffer, initialized to the
     * contents of data.
     *
     * @param data Data to initialize buffer with.
     * @param count Bytes of space to allocate.
     */
    void allocate(const void *data, int count);

    /**
     * Replaces the count bytes of this buffer starting at offset with the
     * contents of data. Any other bytes in the buffer will be left unmodified.
     *
     * It is assumed that create() has been called on this buffer and that it
     * has been bound to the current context.
     *
     * @param offset Buffer offset at which to start writing data.
     * @param data Data to write.
     * @param count Number of bytes to write.
     */
    void write(int offset, const void *data, int count);

 private:
    GLenum target;
    GLenum usage = GL_STATIC_DRAW;
    GLuint buffer = 0;
};

}  // namespace ge
