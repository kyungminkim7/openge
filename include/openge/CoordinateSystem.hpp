#pragma once

#include <glm/fwd.hpp>

namespace ge {

/**
 * Right-handed coordinate system.
 *
 * The following convention is used:
 *     - x: forward
 *     - y: left
 *     - z: up
 */
class CoordinateSystem {
 public:
    /**
     * Forward direction.
     */
    static const glm::vec3 FORWARD;

    /**
     * Backwards direction.
     */
    static const glm::vec3 BACK;


    /**
     * Left direction.
     */
    static const glm::vec3 LEFT;

    /**
     * Right direction.
     */
    static const glm::vec3 RIGHT;

    /**
     * Upwards direction.
     */
    static const glm::vec3 UP;

    /**
     * Downwards direction.
     */
    static const glm::vec3 DOWN;

    /**
     * Origin coordinate.
     */
    static const glm::vec3 ORIGIN;
};

}  // namespace ge
