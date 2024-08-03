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
     * Get the value of a global variable in the script.
     *
     * @param name Global variable name.
     * @return Global variable value.
     */
    template<typename T>
    T getGlobal(std::string_view name);

    /**
     * Set the value of a global c-string variable in the script.
     *
     * @param name Name of the global variable to set.
     * @param value Value to set the global variable to.
     */
    void setGlobal(std::string_view name, const char *value);

    /**
     * Set the value of a global string variable in the script.
     *
     * @param name Name of the global variable to set.
     * @param value Value to set the global variable to.
     */
    void setGlobal(std::string_view name, const std::string &value);

    /**
     * Set the value of a global bool variable in the script.
     *
     * @param name Name of the global variable to set.
     * @param value Value to set the global variable to.
     */
    void setGlobal(std::string_view name, bool value);

    /**
     * Set the value of a global float variable in the script.
     *
     * @param name Name of the global variable to set.
     * @param value Value to set the global variable to.
     */
    void setGlobal(std::string_view name, float value);

    /**
     * Set the value of a global double variable in the script.
     *
     * @param name Name of the global variable to set.
     * @param value Value to set the global variable to.
     */
    void setGlobal(std::string_view name, double value);

    /**
     * Set the value of a global int variable in the script.
     *
     * @param name Name of the global variable to set.
     * @param value Value to set the global variable to.
     */
    void setGlobal(std::string_view name, int value);

 private:
    void executeChunk();

    template<typename T>
    T pop();

    template<typename T>
    T top() const;

    lua_State * const state;
};

}  // namespace ge
