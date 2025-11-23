#include <gmock/gmock.h>

#include <functional>
#include <memory>
#include <utility>

#include <openge/GameObject.hpp>
#include <openge/impl/InputSystem.hpp>

using ge::GameObject;
using ge::GameObjectPtr;
using testing::Eq;
using testing::IsEmpty;
using testing::Pointer;
using testing::SizeIs;

struct TestEvent {
    int data = 0;
};

using OnTestEvent = std::function<void(const TestEvent &)>;

class InputSystemListener: public testing::Test {
 protected:
    void SetUp() override {
        ge::InputSystem::addListener<TestEvent>(
            [this](auto listener){ onTestEvent = std::move(listener); },
            &key,
            [this](const auto &){ listenerCalled = true; });
    }

    const int key{42};

    OnTestEvent onTestEvent{};
    bool listenerCalled{false};
};

TEST_F(InputSystemListener, InvokesListenerUponEventBeingTriggered) {
    onTestEvent({});

    ASSERT_TRUE(listenerCalled);
}

TEST_F(InputSystemListener, DoesNotInvokeRemovedListener) {
    ge::InputSystem::removeListener<TestEvent>(&key);

    onTestEvent({});

    ASSERT_FALSE(listenerCalled);
}

TEST_F(InputSystemListener, PassesEventDataToListener) {
    ge::InputSystem::addListener<TestEvent>(
        [this](auto listener){ onTestEvent = std::move(listener); },
        &key,
        [this](const auto &event){
            ASSERT_THAT(event.data, Eq(4));
        });

    onTestEvent({4});
}

class InputSystemListeners: public testing::Test {
 protected:
    const int key1{42};
    const int key2{84};

    OnTestEvent onTestEvent{};
    bool listener1Called{false};
    bool listener2Called{false};
};

TEST_F(InputSystemListeners, InvokesAllListenersUponEventBeingTriggered) {
    const auto registerListener = [this](auto listener){
        onTestEvent = std::move(listener);
    };

    ge::InputSystem::addListener<TestEvent>(
        registerListener,
        &key1,
        [this](const auto &){ listener1Called = true; });

    ge::InputSystem::addListener<TestEvent>(
        registerListener,
        &key2,
        [this](const auto &){ listener2Called = true; });

    onTestEvent({});

    ASSERT_TRUE(listener1Called);
    ASSERT_TRUE(listener2Called);
}

TEST_F(InputSystemListeners, HandlesRemovingListenerDuringEventDispatch) {
    const auto registerListener = [this](auto listener){
        onTestEvent = std::move(listener);
    };

    ge::InputSystem::addListener<TestEvent>(
        registerListener,
        &key1,
        [this](const auto &){
            ge::InputSystem::removeListener<TestEvent>(&key1);
        });

    ge::InputSystem::addListener<TestEvent>(
        registerListener,
        &key2,
        [this](const auto &){
            ge::InputSystem::removeListener<TestEvent>(&key2);
        });

    onTestEvent({});
}
