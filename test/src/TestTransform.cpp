#include <gmock/gmock.h>

#include <glm/geometric.hpp>
#include <glm/trigonometric.hpp>
#include <glm/vec3.hpp>
#include <openge/CoordinateSystem.hpp>
#include <openge/Space.hpp>
#include <openge/Transform.hpp>
#include <openge/test/VecNear.hpp>

using ge::CoordinateSystem;
using ge::Space;
using ge::Transform;
using ge::test::VecNear;
using testing::Eq;
using testing::FloatNear;

TEST(TransformRotate, World) {
  Transform transform;

  transform.rotate(CoordinateSystem::FORWARD, glm::radians(90.0f),
                   Space::World);

  transform.rotate(CoordinateSystem::LEFT, glm::radians(90.0f), Space::World);

  ASSERT_THAT(transform.getForward(), VecNear(CoordinateSystem::DOWN, 0.1f));
  ASSERT_THAT(transform.getLeft(), VecNear(CoordinateSystem::FORWARD, 0.1f));
  ASSERT_THAT(transform.getUp(), VecNear(CoordinateSystem::RIGHT, 0.1f));
}

TEST(TransformRotate, Self) {
  Transform transform;

  transform.rotate(CoordinateSystem::FORWARD, glm::radians(90.0f));
  transform.rotate(CoordinateSystem::LEFT, glm::radians(90.0f));

  ASSERT_THAT(transform.getForward(), VecNear(CoordinateSystem::LEFT, 0.1f));
  ASSERT_THAT(transform.getLeft(), VecNear(CoordinateSystem::UP, 0.1f));
  ASSERT_THAT(transform.getUp(), VecNear(CoordinateSystem::FORWARD, 0.1f));
}

TEST(InverseTransformDirection, TransformsFromWorldSpaceToLocalSpace) {
  Transform transform;
  transform.rotate(CoordinateSystem::UP, glm::radians(90.0f));

  ASSERT_THAT(transform.inverseTransformDirection(CoordinateSystem::FORWARD),
              VecNear(CoordinateSystem::RIGHT, 0.1f));
}

TEST(InverseTransformDirection, MaintainsLength) {
  Transform transform;

  glm::vec3 direction{1.0f, 2.0f, 3.0f};

  ASSERT_THAT(transform.inverseTransformDirection(direction),
              VecNear(direction, 0.1f));
}

TEST(InverseTransformDirection, DoesNotAddPosition) {
  Transform transform;
  transform.setPosition(glm::vec3{1.0f, 2.0f, 3.0f});

  glm::vec3 direction{4.0f, 5.0f, 6.0f};

  ASSERT_THAT(transform.inverseTransformDirection(direction),
              VecNear(direction, 0.1f));
}

TEST(TransformDirection, TransformsFromLocalSpaceToWorldSpace) {
  Transform transform;
  transform.rotate(CoordinateSystem::UP, glm::radians(90.0f));

  ASSERT_THAT(transform.transformDirection(CoordinateSystem::FORWARD),
              VecNear(CoordinateSystem::LEFT, 0.1f));
}

TEST(TransformDirection, MaintainsLength) {
  Transform transform;

  glm::vec3 direction{1.0f, 2.0f, 3.0f};

  ASSERT_THAT(transform.transformDirection(direction),
              VecNear(direction, 0.1f));
}

TEST(TransformDirection, DoesNotAddPosition) {
  Transform transform;
  transform.setPosition(glm::vec3{1.0f, 2.0f, 3.0f});

  glm::vec3 direction{4.0f, 5.0f, 6.0f};

  ASSERT_THAT(transform.transformDirection(direction),
              VecNear(direction, 0.1f));
}

TEST(TransformTranslate, World) {
  constexpr auto distance = 5.0f;
  Transform transform;

  transform.rotate(CoordinateSystem::UP, glm::radians(90.0f), Space::World);
  transform.translate(CoordinateSystem::FORWARD * distance, Space::World);

  ASSERT_THAT(transform.getPosition(),
              VecNear(CoordinateSystem::FORWARD * distance, 0.1));
}

TEST(TransformTranslate, Self) {
  constexpr auto distance = 5.0f;
  Transform transform;

  transform.rotate(CoordinateSystem::UP, glm::radians(90.0f));
  transform.translate(CoordinateSystem::FORWARD * distance);

  ASSERT_THAT(transform.getPosition(),
              VecNear(CoordinateSystem::LEFT * distance, 0.1));
}

TEST(TransformTranslate, TranslatesRelativeToPosition) {
  Transform transform;
  transform.setPosition(CoordinateSystem::FORWARD);

  transform.translate(CoordinateSystem::LEFT);

  ASSERT_THAT(transform.getPosition(),
              VecNear(CoordinateSystem::FORWARD + CoordinateSystem::LEFT, 0.1));
}

TEST(TransformLookAt, RotatesTransformToPointToTarget) {
  Transform transform;
  transform.setPosition(glm::vec3{1.0f, 2.0f, 3.0f});
  const glm::vec3 target{0.0f, 0.0f, 0.0f};
  const auto expectedForward = glm::normalize(target - transform.getPosition());

  transform.lookAt(target);

  ASSERT_THAT(transform.getForward(), VecNear(expectedForward, 0.1f));
}
