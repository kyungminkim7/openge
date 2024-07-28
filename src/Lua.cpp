#include <openge/Lua.hpp>

#include <lua.hpp>

namespace ge {

Lua::Lua() : state(luaL_newstate()) { }

Lua::~Lua() {
    lua_close(state);
}

void Lua::loadScript(std::string_view script) {
    luaL_loadstring(state, script.data());
    lua_pcall(state, 0, 0, 0);
}

std::string Lua::getGlobalString(std::string_view name) {
    lua_getglobal(state, name.data());
    return popString();
}

std::string Lua::popString() {
    std::string result(lua_tostring(state, -1));
    lua_pop(state, 1);
    return result;
}

}  // namespace ge
