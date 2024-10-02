#include <QImage>
#include <string>

#include <openge/GLTexture.hpp>

namespace ge {

using namespace std::string_literals;

GLTexture::GLTexture(const char *filepath, bool generateMipMaps) :
    texture(QImage((":/assets/"s + filepath).c_str()).mirrored(),
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
