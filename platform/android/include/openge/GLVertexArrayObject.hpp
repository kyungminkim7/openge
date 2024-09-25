#pragma once

#include <GLES3/gl32.h>

namespace ge {

/**
 * Wraps an OpenGL vertex array object.
 */
class GLVertexArrayObject {
 public:
    ~GLVertexArrayObject();

    /**
     * Creates the underlying OpenGL vertex array object.
     */
    void create();

    /**
     * Binds the vertex array object to the OpenGL
     * binding point.
     */
    void bind();

    /**
     * Unbinds the vertex array object by binding
     * the default vertex array object (id = 0).
     */
    void release();

 private:
    GLuint vao;
};

}  // namespace ge
