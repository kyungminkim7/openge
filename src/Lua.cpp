#include <openge/Lua.hpp>

#include <stdexcept>

#include <openge/Exception.hpp>

namespace {

template<typename>
struct LuaType;

template<>
struct LuaType<std::string> {
    static constexpr auto value = LUA_TSTRING;
};

template<>
struct LuaType<bool> {
    static constexpr auto value = LUA_TBOOLEAN;
};

template<>
struct LuaType<float> {
    static constexpr auto value = LUA_TNUMBER;
};

template<>
struct LuaType<double> {
    static constexpr auto value = LUA_TNUMBER;
};

template<>
struct LuaType<int> {
    static constexpr auto value = LUA_TNUMBER;
};

template<typename T>
constexpr auto LuaTypeValue = LuaType<T>::value;

}  // namespace

namespace ge {

/**
 * Returns top element of the Lua stack as a string.
 *
 * @return Top element of the Lua stack.
 */
template<>
std::string Lua::top() const {
    return std::string(lua_tostring(state, -1));
}

/**
 * Returns top element of the Lua stack as a bool.
 *
 * @return Top element of the Lua stack.
 */
template<>
bool Lua::top() const {
    return lua_toboolean(state, -1);
}

/**
 * Returns top element of the Lua stack as a float.
 *
 * @return Top element of the Lua stack.
 */
template<>
float Lua::top() const {
    return static_cast<float>(lua_tonumber(state, -1));
}

/**
 * Returns top element of the Lua stack as a double.
 *
 * @return Top element of the Lua stack.
 */
template<>
double Lua::top() const {
    return static_cast<double>(lua_tonumber(state, -1));
}

/**
 * Returns top element of the Lua stack as an int.
 *
 * @return Top element of the Lua stack.
 */
template<>
int Lua::top() const {
    return static_cast<int>(lua_tointeger(state, -1));
}

template<typename T>
T Lua::pop() {
    const auto result = top<T>();
    lua_pop(state, 1);
    return result;
}

Lua::Lua() : state(luaL_newstate()) { }

Lua::~Lua() {
    lua_close(state);
}

void Lua::loadScript(std::string_view script) {
    if (luaL_loadstring(state, script.data()) != LUA_OK) {
        throw BuildError(pop<std::string>());
    }

    executeChunk();
}

void Lua::executeChunk() {
    if (lua_pcall(state, 0, 0, 0) != LUA_OK) {
        throw std::runtime_error(pop<std::string>());
    }
}

template<typename T>
T Lua::getGlobal(std::string_view name) {
    const auto type = lua_getglobal(state, name.data());

    if (type != LuaTypeValue<T>) {
        throw std::invalid_argument(pop<std::string>());
    }

    return pop<T>();
}

void Lua::setGlobal(std::string_view name, const char *value) {
    lua_pushstring(state, value);
    lua_setglobal(state, name.data());
}

void Lua::setGlobal(std::string_view name, const std::string &value) {
    setGlobal(name, value.c_str());
}

void Lua::setGlobal(std::string_view name, bool value) {
    lua_pushboolean(state, value);
    lua_setglobal(state, name.data());
}

void Lua::setGlobal(std::string_view name, float value) {
    lua_pushnumber(state, static_cast<LUA_NUMBER>(value));
    lua_setglobal(state, name.data());
}

void Lua::setGlobal(std::string_view name, double value) {
    lua_pushnumber(state, static_cast<LUA_NUMBER>(value));
    lua_setglobal(state, name.data());
}

void Lua::setGlobal(std::string_view name, int value) {
    lua_pushnumber(state, static_cast<LUA_INTEGER>(value));
    lua_setglobal(state, name.data());
}

template std::string Lua::getGlobal<std::string>(std::string_view name);
template bool Lua::getGlobal<bool>(std::string_view name);
template float Lua::getGlobal<float>(std::string_view name);
template double Lua::getGlobal<double>(std::string_view name);
template int Lua::getGlobal<int>(std::string_view name);

}  // namespace ge
