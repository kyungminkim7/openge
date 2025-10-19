#include <openge/InputSystem.hpp>
#include <utility>

namespace ge {

template<typename Event, typename Listener>
void Component::addInputListener(Listener listener) {
    cleanUp.emplace_back([this]() {
        InputSystem::removeListener<Event>(this);
    });

    InputSystem::addListener<Event>(this, std::move(listener));
}

}  // namespace ge