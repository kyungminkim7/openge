#include <gmock/gmock.h>

#include <memory>

#include <openge/Event.hpp>
#include <openge/GameObject.hpp>
#include <openge/InputSystem.hpp>
#include <openge/KeyEvent.hpp>
#include <openge/UI.hpp>

using ge::GameObject;
using testing::Pointer;

class InputCallback : public testing::Test {
 protected:
    InputCallback() :
        event(ge::Event::Type::KeyPress,
              ge::UI::Key::Key_Up,
              ge::UI::KeyboardModifier::NoModifier),
        listenerCalled(std::make_shared<bool>(false)) {}

    const ge::KeyEvent event;
    std::shared_ptr<bool> listenerCalled;
};

TEST_F(InputCallback, IsInvokedUponInputEvent) {
    auto gameObject = GameObject::create();

    ge::InputSystem::addOnKeyPressListener(gameObject,
        [listenerCalled = listenerCalled](auto, const auto &){
            *listenerCalled = true;
        });

    ge::InputSystem::onKeyPress(event);

    ASSERT_TRUE(*listenerCalled);
}

TEST_F(InputCallback, IsRemovedUponGameObjectDestruction) {
    auto gameObject = GameObject::create();

    ge::InputSystem::addOnKeyPressListener(gameObject,
        [listenerCalled = listenerCalled](auto, const auto &){
            *listenerCalled = true;
        });

    gameObject.reset();

    ge::InputSystem::onKeyPress(event);

    ASSERT_FALSE(*listenerCalled);
}

TEST_F(InputCallback, PassesOriginalGameObject) {
    auto gameObject = GameObject::create();
    auto gameObjectPointer = gameObject.get();

    ge::InputSystem::addOnKeyPressListener(gameObject,
        [gameObjectPointer](auto gameObject, const auto &){
            ASSERT_THAT(gameObject, Pointer(gameObjectPointer));
        });

    ge::InputSystem::onKeyPress(event);
}
