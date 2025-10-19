#pragma once

#include <functional>
#include <iterator>
#include <utility>
#include <map>

namespace ge::InputSystem {

template<typename Event>
using EventListener = std::function<void(const Event &)>;

template<typename T, typename Event>
std::map<const T *, EventListener<Event>> listeners{};

template<typename Event, typename RegisterListener,
         typename T, typename Listener>
void addListener(RegisterListener registerListener,
                 const T *key, Listener listener) {
    static auto init = [registerListener=std::move(registerListener)]() {
        registerListener([](const Event &event) {
            for (auto iter = std::begin(listeners<T, Event>);
                 iter != std::end(listeners<T, Event>); ) {
                const auto pos = iter++;
                const auto & [key, listener] = *pos;
                listener(event);
            }
        });

        return true;
    }();

    listeners<T, Event>[key] = std::move(listener);
};

template<typename Event, typename T>
void removeListener(const T *key) {
    listeners<T, Event>.erase(key);
}

}  // namespace ge::InputSystem
