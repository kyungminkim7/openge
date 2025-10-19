#pragma once

#include <algorithm>
#include <memory>
#include <utility>
#include <vector>

#include <openge/Component.hpp>

namespace ge {

template<typename T, typename... Args>
std::shared_ptr<T> GameObject::addComponent(Args&&... args) {
    const auto type = getComponentTypeIndex<T>();

    const auto component = std::make_shared<T>(shared_from_this(),
                                               std::forward<Args>(args)...);
    component->init();

    components[type].emplace_back(component);

    return component;
}

template<typename T>
std::shared_ptr<T> GameObject::getComponent() {
    const auto type = getComponentTypeIndex<T>();
    const auto iter = components.find(type);
    return iter == components.end() ?
        nullptr : std::static_pointer_cast<T>(iter->second.front());
}

template<typename T>
std::vector<std::shared_ptr<T>> GameObject::getComponents() {
    const auto type = getComponentTypeIndex<T>();
    const auto iter = components.find(type);

    if (iter == components.end()) {
        return {};
    } else {
        std::vector<std::shared_ptr<T>> attachedComponents(iter->second.size());
        std::transform(iter->second.cbegin(), iter->second.cend(),
                       attachedComponents.begin(),
                       std::static_pointer_cast<T, Component>);
        return attachedComponents;
    }
}

template<typename T>
std::type_index GameObject::getComponentTypeIndex() const {
    return std::type_index(typeid(T));
}

}  // namespace ge
