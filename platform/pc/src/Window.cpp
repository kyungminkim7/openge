#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

#include <string>
#include <utility>
#include <vector>

#include <openge/Exception.hpp>
#include <openge/KeyEvent.hpp>
#include <openge/OpenGL.hpp>
#include <openge/Window.hpp>

namespace {

GLFWwindow *window = nullptr;

std::vector<ge::Window::KeyListener> keyListeners{};

void errorCallback(int error, const char *description) {
    spdlog::error("GLFW Error ({}): {}", error, description);
}

void initializeWindowingSystem() {
    glfwSetErrorCallback(errorCallback);

    spdlog::info("Initializing GLFW");

    if (!glfwInit()) {
        throw ge::WindowError("Failed to initialize GLFW");
    }
}

void createWindow(unsigned int width, unsigned int height,
                  const std::string &title) {
    spdlog::info("Creating window");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

    if (window == nullptr) {
        throw ge::WindowError("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        throw ge::WindowError("Failed to initialize GLAD");
    }
}

void framebufferSizeCallback(GLFWwindow *, int width, int height) {
    glViewport(0, 0, width, height);
}

void keyCallback(GLFWwindow *, int key, int scancode, int action, int mods) {
    const ge::KeyEvent event {
        ge::KeyEvent::Key{key},
        scancode,
        ge::KeyEvent::Action{action},
        ge::KeyEvent::Modifier{mods}
    };

    for (const auto &listener : keyListeners) {
        listener(event);
    }
}

}  // namespace

namespace ge::Window {

void addListener(KeyListener listener) {
    keyListeners.push_back(std::move(listener));
}

void create(unsigned int width, unsigned int height, const std::string &title) {
    if (window != nullptr) {
        throw WindowError("Creating multiple windows are not supported");
    }

    initializeWindowingSystem();
    createWindow(width, height, title);

    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetKeyCallback(window, keyCallback);
}

void close() {
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

bool isOpen() {
    return glfwWindowShouldClose(window) == GLFW_FALSE;
}

void destroy() {
    spdlog::info("Destroying window");
    keyListeners.clear();
    glfwDestroyWindow(window);

    spdlog::info("Terminating GLFW");
    glfwTerminate();
}

void pollEvents() {
    glfwPollEvents();
}

void swapBuffers() {
    glfwSwapBuffers(window);
}

}  // namespace ge::Window
