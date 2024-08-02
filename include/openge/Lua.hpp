#pragma once

#include <string>
#include <string_view>

#include <lua.hpp>

namespace ge {

/**
 * Scripting engine for executing Lua scripts.
 */
class Lua {
 public:
    Lua();
    ~Lua();

    /**
     * Compiles and executes the given string as an embedded script.
     * 
     * @param script Inline script code to load and execute.
     */
    void loadScript(std::string_view script);

    /**
     * Get the value of a global string variable in the script.
     *
     * @param name Global variable name.
     * @return Global variable value.
     */
    std::string getGlobalString(std::string_view name);

    /**
     * Set the value of a global string variable in the script.
     *
     * @param name Name of the global variable to set.
     * @param value Value to set the global variable to.
     */
    void setGlobal(std::string_view name, std::string_view value);

 private:
    void executeChunk();
    std::string popString();

    lua_State * const state;
};

}  // namespace ge
