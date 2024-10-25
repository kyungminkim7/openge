#include <openge/Color.hpp>

namespace {

constexpr float COLOR_COMPONENT_MAX_F = 255.0f;

}  // namespace

namespace ge {

Color::Color(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a) :
    r(r), g(g), b(b), a(a) {}

std::uint8_t Color::alpha() const {
    return a;
}

float Color::alphaF() const {
    return a / COLOR_COMPONENT_MAX_F;
}

std::uint8_t Color::blue() const {
    return b;
}

float Color::blueF() const {
    return b / COLOR_COMPONENT_MAX_F;
}

std::uint8_t Color::green() const {
    return g;
}

float Color::greenF() const {
    return g / COLOR_COMPONENT_MAX_F;
}

std::uint8_t Color::red() const {
    return r;
}

float Color::redF() const {
    return r / COLOR_COMPONENT_MAX_F;
}

void Color::setAlpha(std::uint8_t alpha) {
    a = alpha;
}

}  // namespace ge
