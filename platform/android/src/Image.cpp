#include <android/data_space.h>

#include <algorithm>
#include <stdexcept>
#include <string>

#include "openge/ImageDecoder.hpp"
#include <openge/Image.hpp>

namespace {

constexpr auto NUM_CHANNELS = 4;

}  // namespace

namespace ge {

Image::Image(const char *filepath) {
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
    if (stride != imageWidth * NUM_CHANNELS) {
        throw std::length_error("Image decoder padded image "s + filepath);
    }

    const auto size = imageHeight * stride;
    pixels = decoder.decodeImage(stride, size);
}

int Image::width() const {
    return imageWidth;
}

int Image::height() const {
    return imageHeight;
}

std::uint8_t * Image::bits() {
    return pixels.data();
}

const std::uint8_t * Image::bits() const {
    return pixels.data();
}

void Image::mirror(bool horizontal, bool vertical) {
    if (horizontal) {
        mirrorHorizontal();
    }

    if (vertical) {
        mirrorVertical();
    }
}

Image Image::mirrored(bool horizontal, bool vertical) const {
    Image image(*this);
    image.mirror(horizontal, vertical);
    return image;
}

void Image::mirrorHorizontal() {
    auto data = bits();
    for (auto row = 0; row < height(); ++row) {
        for (auto col = 0; col < width() / 2; ++col) {
            for (auto channel = 0; channel < NUM_CHANNELS; ++channel) {
                std::swap(
                    data[NUM_CHANNELS * (row * width() + col) + channel],
                    data[NUM_CHANNELS * ((row + 1) * width() - col - 1) +
                         channel]);
            }
        }
    }
}

void Image::mirrorVertical() {
    auto data = bits();
    for (auto row = 0; row < height() / 2; ++row) {
        for (auto col = 0; col < width(); ++col) {
            for (auto channel = 0; channel < NUM_CHANNELS; ++channel) {
                std::swap(
                    data[NUM_CHANNELS * (row * width() + col) + channel],
                    data[NUM_CHANNELS * ((height() - row - 1) * width() + col) +
                         channel]);
            }
        }
    }
}

}  // namespace ge
