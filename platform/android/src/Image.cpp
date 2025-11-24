#include <android/data_space.h>

#include <openge/Image.hpp>
#include <openge/ImageDecoder.hpp>
#include <string>

namespace ge {

Image::Image(const char* filepath) : numChannels(4) {
  using namespace std::string_literals;

  ImageDecoder decoder(filepath);
  decoder.setAndroidBitmapFormat(ANDROID_BITMAP_FORMAT_RGBA_8888);
  decoder.setUnpremultipliedRequired(true);

  const auto dataSpace = decoder.getDataSpace();
  if (dataSpace != ADATASPACE_SCRGB && dataSpace != ADATASPACE_SRGB &&
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

}  // namespace ge
