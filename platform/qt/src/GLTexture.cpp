#include <QImage>

#include <openge/GLTexture.hpp>

namespace ge {

GLTexture::GLTexture(const char *filepath, bool generateMipMaps) :
    texture(QImage(filepath).mirrored(),
            generateMipMaps ? QOpenGLTexture::GenerateMipMaps :
                              QOpenGLTexture::DontGenerateMipMaps) { }

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
