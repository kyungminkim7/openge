#pragma once

#include <cstdint>
#include <vector>

namespace ge {

class Color;

/**
 * Image representation allowing direct acess to pixel data.
 */
class Image {
 public:
    /**
     * Image formats
     */
    enum class Format {
        Format_RGBA8888
    };

    /**
     * Loads an image from a file.
     * 
     * @param filepath Image filepath.
     */
    explicit Image(const char *filepath);

    /**
     * Constructs an image.
     *
     * @note This will create an image with uninitialized data.
     *       Call fill() to fill the image with pixel values
     *       before use.
     *
     * @param imageWidth Image width.
     * @param imageHeight Image height.
     * @param imageFormat Image format.
     */
    Image(int imageWidth, int imageHeight, Format imageFormat);

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
     * Fills the entire image with the given color.
     *
     * @param color Color to fill the image with.
     */
    void fill(const Color &color);

    /**
     * Returns the image height.
     *
     * @return Image height.
     */
    int height() const;

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

    /**
     * Returns the image width.
     *
     * @return Image width.
     */
    int width() const;

 private:
    void load();

    void mirrorHorizontal();
    void mirrorVertical();

    int numChannels;
    std::vector<std::uint8_t> image;
    int imageWidth;
    int imageHeight;
};

}  // namespace ge
