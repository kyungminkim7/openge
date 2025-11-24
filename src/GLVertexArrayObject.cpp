#include <openge/GLVertexArrayObject.hpp>

namespace ge {

GLVertexArrayObject::~GLVertexArrayObject() { glDeleteVertexArrays(1, &vao); }

void GLVertexArrayObject::create() { glGenVertexArrays(1, &vao); }

void GLVertexArrayObject::bind() { glBindVertexArray(vao); }

void GLVertexArrayObject::release() { glBindVertexArray(0); }

}  // namespace ge
