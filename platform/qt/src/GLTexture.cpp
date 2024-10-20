#include <QImage>

#include <openge/GLTexture.hpp>

namespace ge {

GLTexture::GLTexture(const char *filepath, MipMapGeneration genMipMaps) :
    texture(QImage(filepath).mirrored(),
            genMipMaps) {}

void GLTexture::bind(unsigned int unit) {
    texture.bind(unit);
}

void GLTexture::setWrapMode(WrapMode mode) {
    texture.setWrapMode(mode);
}

void GLTexture::setMinificationFilter(Filter filter) {
    texture.setMinificationFilter(filter);
}

void GLTexture::setMagnificationFilter(Filter filter) {
    texture.setMagnificationFilter(filter);
}

}  // namespace ge
