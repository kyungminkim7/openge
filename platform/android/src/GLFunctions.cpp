#include <openge/GLFunctions.hpp>

namespace ge {

void GLFunctions::glViewport(GLint x, GLint y,
                             GLsizei width, GLsizei height) {
    ::glViewport(x, y, width, height);
}

void GLFunctions::glClearColor(GLclampf red, GLclampf green, GLclampf blue,
                               GLclampf alpha) {
    ::glClearColor(red, green, blue, alpha);
}

void GLFunctions::glClear(GLbitfield mask) {
    ::glClear(mask);
}

}  // namespace ge
