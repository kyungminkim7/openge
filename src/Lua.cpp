#include <openge/Lua.hpp>

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

Lua::Lua() : state(luaL_newstate()) {
    luaL_openlibs(state);
}

Lua::~Lua() {
    lua_close(state);
}

void Lua::load(const char *script) {
    if (luaL_loadstring(state, script) != LUA_OK) {
        throw BuildError(pop<std::string>());
    }

    executeChunk(0, 0);
}

void Lua::executeChunk(int numArgs, int numResults) {
    if (lua_pcall(state, numArgs, numResults, 0) != LUA_OK) {
        throw std::runtime_error(pop<std::string>());
    }
}

std::size_t Lua::getStackSize() const {
    return lua_gettop(state);
}

template<typename T>
T Lua::getGlobal(const char *name) {
    const auto type = lua_getglobal(state, name);

    if (type != LuaTypeValue<T>) {
        throw std::invalid_argument(pop<std::string>());
    }

    return pop<T>();
}

template std::string Lua::getGlobal<std::string>(const char *name);
template bool Lua::getGlobal<bool>(const char *name);
template float Lua::getGlobal<float>(const char *name);
template double Lua::getGlobal<double>(const char *name);
template int Lua::getGlobal<int>(const char *name);

void Lua::push(const char *value) {
    lua_pushstring(state, value);
}

void Lua::push(const std::string &value) {
    lua_pushstring(state, value.c_str());
}

void Lua::push(bool value) {
    lua_pushboolean(state, value);
}

void Lua::push(float value) {
    lua_pushnumber(state, static_cast<LUA_NUMBER>(value));
}

void Lua::push(double value) {
    lua_pushnumber(state, static_cast<LUA_NUMBER>(value));
}

void Lua::push(int value) {
    lua_pushinteger(state, static_cast<LUA_INTEGER>(value));
}

template<typename T>
T Lua::popElement() {
    const auto result = top<T>();
    lua_pop(state, 1);
    return result;
}

template std::string Lua::popElement<std::string>();
template bool Lua::popElement<bool>();
template float Lua::popElement<float>();
template double Lua::popElement<double>();
template int Lua::popElement<int>();

void Lua::popTable(const char *table) {
    const auto type = lua_getglobal(state, table);
    if (type != LUA_TTABLE) {
        throw std::invalid_argument(pop<std::string>());
    }
}

}  // namespace ge
