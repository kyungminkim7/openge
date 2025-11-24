#include <gmock/gmock.h>

#include <openge/Component.hpp>
#include <openge/GameObject.hpp>
#include <openge/Transform.hpp>

using ge::Component;
using ge::GameObject;
using ge::Transform;
using testing::IsEmpty;
using testing::IsNull;
using testing::NotNull;
using testing::SizeIs;

TEST(GetComponent, ReturnsNullptrIfComponentIsNotAttached) {
  auto gameObject = GameObject::create();
  ASSERT_THAT(gameObject->getComponent<Component>(), IsNull());
}

TEST(AGameObject, HasATransform) {
  auto gameObject = GameObject::create();
  ASSERT_THAT(gameObject->getComponent<Transform>(), NotNull());
}

TEST(GetComponents, ReturnsEmptyListIfComponentsAreNotAttached) {
  auto gameObject = GameObject::create();
  ASSERT_THAT(gameObject->getComponents<Component>(), IsEmpty());
}

TEST(GetComponents, ReturnsListOfAttachedComponents) {
  auto gameObject = GameObject::create();
  gameObject->addComponent<Component>();
  ASSERT_THAT(gameObject->getComponents<Component>(), SizeIs(1));
}
