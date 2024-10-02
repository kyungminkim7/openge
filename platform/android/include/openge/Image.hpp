#pragma once

#include <cstdint>
#include <vector>

namespace ge {

/**
 * Decodes images.
 */
class Image {
 public:
    /**
     * Loads an image from a file.
     * 
     * @param filepath Image filepath.
     */
    explicit Image(const char *filepath);

    /**
     * Returns the image width.
     *
     * @return Image width.
     */
    int width() const;

    /**
     * Returns the image height.
     *
     * @return Image height.
     */
    int height() const;

    /**
     * Returns a pointer to the first pixel data.
     *
     * @return Pixel data
     */
    std::uint8_t * bits();

    /**
     * Returns a pointer to the first pixel data.
     *
     * @return Pixel data
     */
    const std::uint8_t * bits() const;

    /**
     * Mirrors the image.
     *
     * @param horizontal Mirror image in the horizontal direction.
     * @param vertical Mirror image in the vertical direction.
     */
    void mirror(bool horizontal = false, bool vertical = true);

    /**
     * Returns a mirror of the image.
     *
     * @param horizontal Mirror image in the horizontal direction.
     * @param vertical Mirror image in the vertical direction.
     */
    Image mirrored(bool horizontal = false, bool vertical = true) const;

 private:
    void load();

    void mirrorHorizontal();
    void mirrorVertical();

    std::vector<std::uint8_t> pixels;
    int imageWidth;
    int imageHeight;
};

}  // namespace ge
