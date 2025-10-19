#include <algorithm>
#include <array>
#include <stdexcept>

#include <openge/Color.hpp>
#include <openge/Image.hpp>

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

Image::Image(int imageWidth, int imageHeight, Format imageFormat) :
    numChannels(getNumChannels(imageFormat)),
    image(numChannels * imageWidth * imageHeight),
    imageWidth(imageWidth), imageHeight(imageHeight) { }

Image Image::convertToFormat(Image::Format format) {
    switch (format) {
        case ge::Image::Format::Format_RGBA8888:
            return *this;

        default:
            throw std::invalid_argument("Image format is not supported");
    }
}

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
