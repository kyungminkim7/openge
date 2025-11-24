#include <stb_image.h>

#include <algorithm>
#include <openge/Exception.hpp>
#include <openge/Image.hpp>
#include <string>

namespace ge {

Image::Image(const char* filepath) {
  stbi_set_flip_vertically_on_load(true);

  auto* data = stbi_load(filepath, &imageWidth, &imageHeight, &numChannels, 0);

  if (!data) {
    using namespace std::string_literals;
    throw LoadError("Failed to load image "s + filepath + ": " +
                    stbi_failure_reason());
  }

  image.resize(imageWidth * imageHeight * numChannels);
  std::copy(data, data + image.size(), image.begin());

  stbi_image_free(data);
}

}  // namespace ge
