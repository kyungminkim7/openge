#include <openge/GLTexture.hpp>
#include <openge/Image.hpp>
#include <type_traits>

namespace ge {

GLTexture::GLTexture(const Image& image, MipMapGeneration genMipMaps)
    : target(static_cast<std::underlying_type_t<Target>>(Target::Target2D)) {
  glGenTextures(1, &texture);
  glBindTexture(target, texture);
  glTexImage2D(target, 0, GL_RGBA, image.width(), image.height(), 0, GL_RGBA,
               GL_UNSIGNED_BYTE, image.bits());

  if (genMipMaps == MipMapGeneration::GenerateMipMaps) {
    glGenerateMipmap(target);
  }
}

GLTexture::~GLTexture() { glDeleteTextures(1, &texture); }

void GLTexture::bind(unsigned int unit) {
  glActiveTexture(GL_TEXTURE0 + unit);
  glBindTexture(target, texture);
}

void GLTexture::setWrapMode(WrapMode mode) {
  const auto wrapMode = static_cast<std::underlying_type_t<WrapMode>>(mode);
  glTexParameteri(target, GL_TEXTURE_WRAP_S, wrapMode);
  glTexParameteri(target, GL_TEXTURE_WRAP_T, wrapMode);
}

void GLTexture::setMinificationFilter(Filter filter) {
  glTexParameteri(target, GL_TEXTURE_MIN_FILTER,
                  static_cast<std::underlying_type_t<Filter>>(filter));
}

void GLTexture::setMagnificationFilter(Filter filter) {
  glTexParameteri(target, GL_TEXTURE_MAG_FILTER,
                  static_cast<std::underlying_type_t<Filter>>(filter));
}

}  // namespace ge
