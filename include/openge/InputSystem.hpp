#pragma once

#include <functional>
#include <memory>

#include <openge/KeyEvent.hpp>
#include <openge/MouseEvent.hpp>

namespace ge {

class GameObject;

namespace InputSystem {

using OnKeyEventListener =
    std::function<void(std::shared_ptr<GameObject>, const KeyEvent &)>;

using OnMouseEventListener =
    std::function<void(std::shared_ptr<GameObject> , const MouseEvent &)>;

/**
 * Add a callback function to be invoked when a key press event occurs.
 *
 * @param gameObject Game object owning the listener that will be passed to the
 *                   listener when invoked.
 * @param listener Event callback function - will be removed if all instances
 *                 of the owning game object are destroyed.
 */
void addOnKeyPressListener(std::weak_ptr<GameObject> gameObject,
                           OnKeyEventListener listener);

/**
 * Add a callback function to be invoked when a key release event occurs.
 *
 * @param gameObject Game object owning the listener that will be passed to the
 *                   listener when invoked.
 * @param listener Event callback function - will be removed if all instances
 *                 of the owning game object are destroyed.
 */
void addOnKeyReleaseListener(std::weak_ptr<GameObject> gameObject,
                             OnKeyEventListener listener);

/**
 * Add a callback function to be invoked when a mouse move event occurs.
 *
 * @param gameObject Game object owning the listener that will be passed to the
 *                   listener when invoked.
 * @param listener Event callback function - will be removed if all instances
 *                 of the owning game object are destroyed.
 */
void addOnMouseMoveListener(std::weak_ptr<GameObject> gameObject,
                            OnMouseEventListener listener);

/**
 * Add a callback function to be invoked when a mouse press event occurs.
 *
 * @param gameObject Game object owning the listener that will be passed to the
 *                   listener when invoked.
 * @param listener Event callback function - will be removed if all instances
 *                 of the owning game object are destroyed.
 */
void addOnMousePressListener(std::weak_ptr<GameObject> gameObject,
                             OnMouseEventListener listener);

/**
 * Add a callback function to be invoked when a mouse release event occurs.
 *
 * @param gameObject Game object owning the listener that will be passed to the
 *                   listener when invoked.
 * @param listener Event callback function - will be removed if all instances
 *                 of the owning game object are destroyed.
 */
void addOnMouseReleaseListener(std::weak_ptr<GameObject> gameObject,
                               OnMouseEventListener listener);

/**
 * Triggers key press event listeners.
 *
 * @param event Key press event.
 */
void onKeyPress(const KeyEvent &event);

/**
 * Triggers key release event listeners.
 *
 * @param event Key release event.
 */
void onKeyRelease(const KeyEvent &event);

/**
 * Triggers mouse move event listeners.
 *
 * @param event Mouse move event.
 */
void onMouseMove(const MouseEvent &event);

/**
 * Triggers mouse press event listeners.
 *
 * @param event Mouse press event.
 */
void onMousePress(const MouseEvent &event);

/**
 * Triggers mouse release event listeners.
 *
 * @param event Mouse release event.
 */
void onMouseRelease(const MouseEvent &event);

}  // namespace InputSystem
}  // namespace ge
