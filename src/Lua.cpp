#include <openge/Lua.hpp>

#include <stdexcept>

#include <lua.hpp>

#include <openge/Exception.hpp>

namespace ge {

Lua::Lua() : state(luaL_newstate()) { }

Lua::~Lua() {
    lua_close(state);
}

void Lua::execute(std::string_view script) {
    if (luaL_loadstring(state, script.data()) != LUA_OK) {
        throw BuildError(popString());
    }

    executeChunk();
}

void Lua::executeChunk() {
    if (lua_pcall(state, 0, 0, 0) != LUA_OK) {
        throw std::runtime_error(popString());
    }
}

std::string Lua::getGlobalString(std::string_view name) {
    const auto type = lua_getglobal(state, name.data());

    if (type != LUA_TSTRING) {
        throw std::invalid_argument(popString());
    }

    return popString();
}

std::string Lua::popString() {
    std::string result(lua_tostring(state, -1));
    lua_pop(state, 1);
    return result;
}

}  // namespace ge
