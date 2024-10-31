#include <type_traits>

#include <openge/GLBuffer.hpp>

namespace ge {

GLBuffer::GLBuffer(Type type) :
    target(static_cast<std::underlying_type_t<Type>>(type)) { }

GLBuffer::~GLBuffer() {
    glDeleteBuffers(1, &buffer);
}

void GLBuffer::create() {
    glGenBuffers(1, &buffer);
}

void GLBuffer::setUsagePattern(UsagePattern usage) {
    this->usage = static_cast<std::underlying_type_t<UsagePattern>>(usage);
}

void GLBuffer::bind() {
    glBindBuffer(target, buffer);
}

void GLBuffer::allocate(int count) {
    glBufferData(target, count, nullptr, usage);
}

void GLBuffer::allocate(const void *data, int count) {
    glBufferData(target, count, data, usage);
}

void GLBuffer::write(int offset, const void *data, int count) {
    glBufferSubData(target, offset, count, data);
}

}  // namespace ge
