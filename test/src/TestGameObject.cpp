#include <gmock/gmock.h>

#include <memory>

#include <openge/GameObject.hpp>
#include <openge/Mesh.hpp>
#include <openge/Transform.hpp>

using ge::GameObject;
using ge::Mesh;
using ge::Transform;
using testing::IsEmpty;
using testing::IsNull;
using testing::Not;
using testing::NotNull;

TEST(GetComponent, ReturnsNullptrIfComponentIsNotAttached) {
    auto gameObject = GameObject::create();
    ASSERT_THAT(gameObject->getComponent<Mesh>(), IsNull());
}

TEST(AGameObject, HasATransform) {
    auto gameObject = GameObject::create();
    ASSERT_THAT(gameObject->getComponent<Transform>(), NotNull());
}

TEST(GetComponents, ReturnsEmptyListIfComponentsAreNotAttached) {
    auto gameObject = GameObject::create();
    ASSERT_THAT(gameObject->getComponents<Mesh>(), IsEmpty());
}

TEST(GetComponents, ReturnsListOfAttachedComponents) {
    auto gameObject = GameObject::create();
    gameObject->addComponent(std::make_shared<Mesh>(gameObject));
    ASSERT_THAT(gameObject->getComponents<Mesh>(), Not(IsEmpty()));
}
