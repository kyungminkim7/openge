#pragma once

#include <functional>
#include <memory>

#include <openge/KeyEvent.hpp>

namespace ge {

class GameObject;

namespace InputSystem {

using OnKeyEventListener = std::function<void(GameObject *, const KeyEvent &)>;

void addOnKeyPressListener(std::shared_ptr<GameObject> gameObject,
                           OnKeyEventListener listener);

void addOnKeyReleaseListener(std::shared_ptr<GameObject> gameObject,
                             OnKeyEventListener listener);

void onKeyPress(const KeyEvent &event);

void onKeyRelease(const KeyEvent &event);

}  // namespace InputSystem
}  // namespace ge
