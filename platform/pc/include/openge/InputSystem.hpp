#pragma once

#include <functional>
#include <memory>
#include <utility>

#include <openge/Window.hpp>

namespace ge {

class GameObject;

namespace InputSystem {

/**
 * Add an event listener to the input system for a game object.
 *
 * @param key The key identifying the listener (typically a Component).
 * @param listener The listener to add.
 */
template<typename Event, typename T, typename Listener>
inline void addListener(const T *key, Listener listener) {
    addListener<Event>(&ge::Window::addListener, key, std::move(listener));
}

}  // namespace InputSystem
}  // namespace ge

#include <openge/impl/InputSystem.hpp>
