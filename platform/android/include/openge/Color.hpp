#pragma once

#include <cstdint>

namespace ge {

/**
 * Provides colors.
 */
class Color {
 public:
    /**
     * Constructs a color.
     *
     * @param r Red component.
     * @param g Green component.
     * @param b Blue component.
     * @param a Transparency component.
     */
    Color(std::uint8_t r, std::uint8_t g, std::uint8_t b,
          std::uint8_t a = 0xFF);

    /**
     * Returns the alpha color component of this color.
     *
     * @return Alpha color component.
     */
    std::uint8_t alpha() const;

    /**
     * Returns the alpha color component of this color.
     *
     * @return Alpha color component.
     */
    float alphaF() const;

    /**
     * Returns the blue color component of this color.
     *
     * @return Blue color component.
     */
    std::uint8_t blue() const;

    /**
     * Returns the blue color component of this color.
     *
     * @return Blue color component.
     */
    float blueF() const;

    /**
     * Returns the green color component of this color.
     *
     * @return Green color component.
     */
    std::uint8_t green() const;

    /**
     * Returns the green color component of this color.
     *
     * @return Green color component.
     */
    float greenF() const;

    /**
     * Returns the red color component of this color.
     *
     * @return Red color component.
     */
    std::uint8_t red() const;

    /**
     * Returns the red color component of this color.
     *
     * @return Red color component.
     */
    float redF() const;

    /**
     * Sets the alpha color component.
     *
     * @param alpha Alpha color component.
     */
    void setAlpha(std::uint8_t alpha);

 private:
    std::uint8_t r;
    std::uint8_t g;
    std::uint8_t b;
    std::uint8_t a;
};

}  // namespace ge
