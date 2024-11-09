#include <vector>
#include <utility>

#include <openge/InputSystem.hpp>

namespace {

std::vector<
    std::pair<std::weak_ptr<ge::GameObject>,
              ge::InputSystem::OnKeyEventListener>> onKeyPressListeners;

std::vector<
    std::pair<std::weak_ptr<ge::GameObject>,
              ge::InputSystem::OnKeyEventListener>> onKeyReleaseListeners;

std::vector<
    std::pair<std::weak_ptr<ge::GameObject>,
              ge::InputSystem::OnMouseEventListener>> onMouseMoveListeners;

std::vector<
    std::pair<std::weak_ptr<ge::GameObject>,
              ge::InputSystem::OnMouseEventListener>> onMousePressListeners;

std::vector<
    std::pair<std::weak_ptr<ge::GameObject>,
              ge::InputSystem::OnMouseEventListener>> onMouseReleaseListeners;

}  // namespace

template<typename Listeners, typename Event>
void onEvent(Listeners *listeners, const Event &event) {
    auto iter = listeners->begin();

    while (iter != listeners->end()) {
        auto gameObject = std::get<0>(*iter).lock();

        if (gameObject == nullptr) {
            iter = listeners->erase(iter);
        } else {
            std::get<1>(*iter)(std::move(gameObject), event);

            // cppcheck-suppress legacyUninitvar
            ++iter;
        }
    }
}

namespace ge::InputSystem {

void addOnKeyPressListener(std::weak_ptr<GameObject> gameObject,
                           OnKeyEventListener listener) {
    onKeyPressListeners.emplace_back(std::make_pair(std::move(gameObject),
                                                    listener));
}

void addOnKeyReleaseListener(std::weak_ptr<GameObject> gameObject,
                             OnKeyEventListener listener) {
    onKeyReleaseListeners.emplace_back(std::make_pair(std::move(gameObject),
                                                      listener));
}

void addOnMouseMoveListener(std::weak_ptr<GameObject> gameObject,
                            OnMouseEventListener listener) {
    onMouseMoveListeners.emplace_back(std::make_pair(std::move(gameObject),
                                                     listener));
}

void addOnMousePressListener(std::weak_ptr<GameObject> gameObject,
                             OnMouseEventListener listener) {
    onMousePressListeners.emplace_back(std::make_pair(std::move(gameObject),
                                                      listener));
}

void addOnMouseReleaseListener(std::weak_ptr<GameObject> gameObject,
                               OnMouseEventListener listener) {
    onMouseReleaseListeners.emplace_back(std::make_pair(std::move(gameObject),
                                                        listener));
}

void onKeyPress(const KeyEvent &event) {
    onEvent(&onKeyPressListeners, event);
}

void onKeyRelease(const KeyEvent &event) {
    onEvent(&onKeyReleaseListeners, event);
}

void onMouseMove(const MouseEvent &event) {
    onEvent(&onMouseMoveListeners, event);
}

void onMousePress(const MouseEvent &event) {
    onEvent(&onMousePressListeners, event);
}

void onMouseRelease(const MouseEvent &event) {
    onEvent(&onMouseReleaseListeners, event);
}

}  // namespace ge::InputSystem
