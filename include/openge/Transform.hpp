#pragma once

#include <memory>

#include <glm/ext/quaternion_float.hpp>
#include <glm/vec3.hpp>
#include <openge/CoordinateSystem.hpp>
#include <openge/Component.hpp>
#include <openge/Space.hpp>

namespace ge {

class GameObject;

/**
 * Position, rotation, and scale of an object.
 *
 * Transforms follow a right-handed coordinate system
 * where:
 *      - forward: x
 *      - left: y
 *      - up: z
 */
class Transform : public Component {
 public:
    /**
     * Construct a transform.
     */
    explicit Transform(const std::shared_ptr<GameObject> &gameObject = nullptr);

    /**
     * Returns a normalized vector representing the forward
     * direction of the transform.
     *
     * @return Forward direction of transform.
     */
    glm::vec3 getForward() const;

    /**
     * Returns a normalized vector representing the left
     * direction of the transform.
     *
     * @return Left direction of transform.
     */
    glm::vec3 getLeft() const;

    /**
     * Returns a normalized vector representing the up
     * direction of the transform.
     *
     * @return Up direction of transform.
     */
    glm::vec3 getUp() const;

    /**
     * Gets the position of the transform in world space.
     *
     * @return Position.
     */
    glm::vec3 getPosition() const;

    /**
     * Gets the rotation of the transform in world space.
     *
     * @return Rotation.
     */
    glm::quat getRotation() const;

    /**
     * Gets the scale of the transform.
     *
     * @return Scale.
     */
    glm::vec3 getScale() const;

    /**
     * Transforms a direction from world space to local space.
     *
     * This operation is not affected by scale or position
     * of the transform. The returned vector has the same
     * length as the original.
     *
     * @param direction Direction in world space.
     * @return Direction in local space.
     */
    glm::vec3 inverseTransformDirection(const glm::vec3 &direction);

    /**
     * Rotates the transform so the forward vector points at
     * a target position and then rotates the transform to point
     * its up direction vector in the direction hinted by the
     * worldUp vector.
     *
     * @param worldPosition Point to look at in world space.
     * @param worldUp Upward direction in world space.
     */
    void lookAt(const glm::vec3 &worldPosition,
                const glm::vec3 &worldUp = CoordinateSystem::UP);

    /**
     * Rotates the object around the given axis.
     *
     * @param axis Axis to apply rotation to.
     * @param radians Rotation angle to apply.
     * @param relativeTo Determines whether to rotate locally
     *                   or relative to world space.
     */
    void rotate(const glm::vec3 &axis, float radians,
                Space relativeTo = Space::Self);

    /**
     * Sets the world space position of the transform.
     *
     * @param position New position to set.
     */
    void setPosition(const glm::vec3 &position);

    /**
     * Sets the world space rotation of the transform.
     *
     * @param rotation New rotation to set.
     */
    void setRotation(const glm::quat &rotation);

    /**
     * Sets the scale of the transform.
     *
     * @param scale New scale to set.
     */
    void setScale(const glm::vec3 &scale);

    /**
     * Transforms direction from local space to world space.
     *
     * This operation is not affected by scale or position
     * of the transform. The returned vector has the same
     * length as the original.
     *
     * @param direction Direction in local space.
     * @return Direction in world space.
     */
    glm::vec3 transformDirection(const glm::vec3 &direction);

    /**
     * Moves the transform in the direction and distance
     * of translation.
     *
     * @param translation Direction and distance to move.
     * @param relativeTo Determines whether to move relative
     *                   relative to local/world space.
     */
    void translate(const glm::vec3 &translation,
                   Space relativeTo = Space::Self);

 private:
    glm::vec3 scale;
    glm::vec3 position;
    glm::quat rotation;
};

}  // namespace ge
