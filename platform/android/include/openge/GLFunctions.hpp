#pragma once

#include <GLES3/gl32.h>

namespace ge {

/**
 * Provides cross-platform access to the OpenGL ES 2.0 API.
 */
class GLFunctions {
 public:
    /**
     *Initializes OpenGL function resolution for the current context.
     */
    void initializeOpenGLFunctions();
};

}  // namespace ge
