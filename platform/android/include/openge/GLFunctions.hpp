#pragma once

#include <GLES3/gl32.h>

namespace ge {

/**
 * Provides cross-platform access to the OpenGL ES 2.0 API.
 */
class GLFunctions {
 public:
    /**
     * Set the viewport.
     *
     * @param x Viewport lower left corner x coordinate.
     * @param y Viewport lower left corner y coordinate.
     * @param width Viewport width.
     * @param height Viewport height.
     */
    void glViewport(GLint x, GLint y,
                    GLsizei width, GLsizei height);

    /**
     * Specify clear values for color buffers.
     *
     * @param red Red value.
     * @param green Green value.
     * @param blue Blue value.
     * @param alpha Alpha value.
     */
    void glClearColor(GLclampf red, GLclampf green, GLclampf blue,
                      GLclampf alpha);

    /**
     * Clear buffers to preset values.
     *
     * @param mask indicating buffers to be cleared.
     */
    void glClear(GLbitfield mask);
};

}  // namespace ge
