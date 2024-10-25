#include <android/data_space.h>

#include <array>
#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <string>

#include <openge/Color.hpp>
#include <openge/Image.hpp>
#include <openge/ImageDecoder.hpp>

namespace {

int getNumChannels(ge::Image::Format format) {
    switch (format) {
        case ge::Image::Format::Format_RGBA8888:
            return 4;

        default:
            throw std::invalid_argument("Image format is not supported");
    }
}

}  // namespace

namespace ge {

Image::Image(const char *filepath) : numChannels(4) {
    using namespace std::string_literals;

    ImageDecoder decoder(filepath);
    decoder.setAndroidBitmapFormat(ANDROID_BITMAP_FORMAT_RGBA_8888);
    decoder.setUnpremultipliedRequired(true);

    const auto dataSpace = decoder.getDataSpace();
    if (dataSpace != ADATASPACE_SCRGB &&
        dataSpace != ADATASPACE_SRGB &&
        dataSpace != ADATASPACE_SCRGB_LINEAR) {
        decoder.setDataSpace(ADATASPACE_SRGB);
    }

    imageWidth = decoder.getWidth();
    imageHeight = decoder.getHeight();
    const auto stride = decoder.getMinimumStride();
    if (stride != imageWidth * numChannels) {
        throw std::length_error("Image decoder padded image "s + filepath);
    }

    const auto size = imageHeight * stride;
    image = decoder.decodeImage(stride, size);
}

Image::Image(int imageWidth, int imageHeight, Format imageFormat) :
    numChannels(getNumChannels(imageFormat)),
    imageWidth(imageWidth), imageHeight(imageHeight) { }

std::uint8_t * Image::bits() {
    return image.data();
}

const std::uint8_t * Image::bits() const {
    return image.data();
}

void Image::fill(const Color &color) {
    std::array<std::uint8_t, 4> colorArray {
        color.red(),
        color.green(),
        color.blue(),
        color.alpha()
    };

    for (auto pixel = image.begin();
         pixel != image.end();
         pixel = std::copy(colorArray.cbegin(),
                           std::next(colorArray.cbegin(), numChannels),
                           pixel)) {}
}

int Image::height() const {
    return imageHeight;
}

void Image::mirror(bool horizontal, bool vertical) {
    if (horizontal) {
        mirrorHorizontal();
    }

    if (vertical) {
        mirrorVertical();
    }
}

void Image::mirrorHorizontal() {
    for (auto row = 0; row < height(); ++row) {
        for (auto col = 0; col < width() / 2; ++col) {
            for (auto channel = 0; channel < numChannels; ++channel) {
                std::swap(
                    image[numChannels * (row * width() + col) + channel],
                    image[numChannels * ((row + 1) * width() - col - 1) +
                          channel]);
            }
        }
    }
}

void Image::mirrorVertical() {
    for (auto row = 0; row < height() / 2; ++row) {
        for (auto col = 0; col < width(); ++col) {
            for (auto channel = 0; channel < numChannels; ++channel) {
                std::swap(
                    image[numChannels * (row * width() + col) + channel],
                    image[numChannels * ((height() - row - 1) * width() + col) +
                          channel]);
            }
        }
    }
}

Image Image::mirrored(bool horizontal, bool vertical) const {
    Image image(*this);
    image.mirror(horizontal, vertical);
    return image;
}

int Image::width() const {
    return imageWidth;
}

}  // namespace ge
