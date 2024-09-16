#pragma once

#include <algorithm>
#include <stdexcept>
#include <string>

namespace ge {

template<typename T>
void Lua::setGlobal(const char *name, T value) {
    push(value);
    lua_setglobal(state, name);
}

template<typename ReturnType, typename... Types>
ReturnType Lua::call(const char *name, Types... args) {
    const auto type = lua_getglobal(state, name);

    if (type != LUA_TFUNCTION) {
        throw std::invalid_argument(pop<std::string>());
    }

    if constexpr(sizeof...(Types) > 0) {
        push(args...);
    }

    if constexpr (isBasicType<ReturnType>) {
        executeChunk(sizeof...(Types), 1);
    } else {
        executeChunk(sizeof...(Types), LUA_MULTRET);
    }

    return pop<ReturnType>();
}

template<typename T>
T Lua::pop() {
    if constexpr (isBasicType<T>) {
        return popElement<T>();
    } else {
        return popContainer<T>();
    }
}

template<typename Container>
Container Lua::popContainer() {
    Container results(getStackSize());
    std::generate(results.rbegin(), results.rend(),
        [this]{ return this->pop<typename Container::value_type>(); });
    return results;
}

template<typename T, typename... Types>
void Lua::push(T arg, Types... args) {
    push(arg);

    if constexpr(sizeof...(Types) > 0) {
        push(args...);
    }
}

template<typename T>
T Lua::getTableEntry(const char *table, const char *key) {
    popTable(table);
    lua_getfield(state, -1, key);
    const auto value = pop<T>();
    lua_pop(state, 1);
    return value;
}

template<typename T>
T Lua::getTableEntry(const char *array, std::size_t index) {
    if (index == 0) {
        throw std::out_of_range("Lua array indexes start from 1");
    }

    popTable(array);
    lua_geti(state, -1, index);
    auto value = pop<T>();
    lua_pop(state, 1);
    return value;
}

template<typename T>
void Lua::setTableEntry(const char *table, const char *key, T value) {
    popTable(table);
    push(value);
    lua_setfield(state, -2, key);
    lua_pop(state, 1);
}

template<typename T>
void Lua::setTableEntry(const char *array, std::size_t index, T value) {
    if (index == 0) {
        throw std::out_of_range("Lua array indexes start from 1");
    }

    popTable(array);
    push(value);
    lua_seti(state, -2, index);
    lua_pop(state, 1);
}

}  // namespace ge
