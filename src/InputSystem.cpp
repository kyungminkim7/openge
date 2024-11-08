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

}  // namespace

template<typename Listeners, typename Event>
void onEvent(Listeners *listeners, const Event &event) {
    auto iter = listeners->begin();

    while (iter != listeners->end()) {
        auto gameObject = std::get<0>(*iter).lock();

        if (gameObject == nullptr) {
            iter = listeners->erase(iter);
        } else {
            std::get<1>(*iter)(gameObject.get(), event);

            // cppcheck-suppress legacyUninitvar
            ++iter;
        }
    }
}

namespace ge::InputSystem {

void addOnKeyPressListener(std::shared_ptr<GameObject> gameObject,
                           OnKeyEventListener listener) {
    onKeyPressListeners.emplace_back(std::make_pair(std::move(gameObject),
                                                    listener));
}

void addOnKeyReleaseListener(std::shared_ptr<GameObject> gameObject,
                             OnKeyEventListener listener) {
    onKeyReleaseListeners.emplace_back(std::make_pair(std::move(gameObject),
                                                      listener));
}

void onKeyPress(const KeyEvent &event) {
    onEvent(&onKeyPressListeners, event);
}

void onKeyRelease(const KeyEvent &event) {
    onEvent(&onKeyReleaseListeners, event);
}

}  // namespace ge::InputSystem
