#pragma once

#include <functional>
#include <string>

namespace ge {

struct KeyEvent;

namespace Window {

/**
 * Keyboard key listener.
 *
 * @param keyEvent Key event.
 */
using KeyListener = std::function<void(const KeyEvent &)>;

/**
 * Adds a key listener for the window.
 *
 * @param listener Key listener function to add.
 */
void addListener(KeyListener listener);

/**
 * Creates a window.
 *
 * @param width Window width in screen coordinates.
 * @param height Window height in screen coordinates.
 * @param title Window title.
 */
void create(unsigned int width, unsigned int height,
            const std::string &title);

/**
 * Closes the window.
 */
void close();

/**
 * Destroys the window.
 */
void destroy();

/**
 * Checks if the window is open.
 *
 * @return True if the window is open, false otherwise.
 */
bool isOpen();

/**
 * Processes events for all windows.
 */
void pollEvents();

/**
 * Swaps the front and back buffers of the window when rendering.
 */
void swapBuffers();

}  // namespace Window
}  // namespace ge
