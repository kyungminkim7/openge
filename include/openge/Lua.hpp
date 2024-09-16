#pragma once

#include <cstddef>
#include <string>
#include <type_traits>

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
    void load(const char *script);

    /**
     * Gets the number of elements on the Lua stack.
     *
     * @return Number of elements on the Lua stack.
     */
    std::size_t getStackSize() const;

    /**
     * Get the value of a global variable in the script.
     *
     * @param name Global variable name.
     * @return Global variable value.
     */
    template<typename T>
    T getGlobal(const char *name);

    /**
     * Set the value of a global variable in the script.
     *
     * @param name Name of the global variable to set.
     * @param value Value to set the global variable to.
     */
    template<typename T>
    void setGlobal(const char *name, T value);

    /**
     * Gets the entry value of a global table.
     *
     * @param table Global table variable name.
     * @param key Table entry key.
     * @return Table entry value.
     */
    template<typename T>
    T getTableEntry(const char *table, const char *key);

    /**
     * Gets the value of an array element.
     *
     * @param array Global array variable name.
     * @param index Array index starting from 1.
     * @return Array element value.
     */
    template<typename T>
    T getTableEntry(const char *array, std::size_t index);

    /**
     * Sets the entry value of a global table.
     *
     * @param table Global table variable name.
     * @param key Table entry key.
     * @param value Table entry value.
     */
    template<typename T>
    void setTableEntry(const char *table, const char *key, T value);

    /**
     * Sets the value of an array element.
     *
     * @param array Global array variable name.
     * @param index Array index starting from 1.
     * @param value Array element value to set.
     */
    template<typename T>
    void setTableEntry(const char *array, std::size_t index, T value);

    /**
     * Call a function in the Lua script.
     * 
     * @return return value of the Lua function.
     */
    template<typename ReturnType, typename... Types>
    ReturnType call(const char *name, Types... args);

    /**
     * Push values onto the Lua stack.
     *
     * @param arg Value to push.
     * @param args Additional values to push.
     */
    template<typename T, typename... Types>
    void push(T arg, Types... args);

    /**
     * Push a c-string onto the Lua stack.
     *
     * @param value Value to push.
     */
    void push(const char *value);

    /**
     * Push a string onto the Lua stack.
     *
     * @param value Value to push.
     */
    void push(const std::string &value);

    /**
     * Push a boolean onto the Lua stack.
     *
     * @param value Value to push.
     */
    void push(bool value);

    /**
     * Push a float onto the Lua stack.
     *
     * @param value Value to push.
     */
    void push(float value);

    /**
     * Push a double onto the Lua stack.
     *
     * @param value Value to push.
     */
    void push(double value);

    /**
     * Push an int onto the Lua stack.
     *
     * @param value Value to push.
     */
    void push(int value);

 private:
    template<typename T>
    static constexpr bool isBasicType =
      std::is_fundamental_v<T> || std::is_convertible_v<T, std::string>;

    void executeChunk(int numArgs, int numResults);

    template<typename T>
    T pop();

    template<typename T>
    T popElement();

    template<typename Container>
    Container popContainer();

    void popTable(const char *table);

    template<typename T>
    T top() const;

    lua_State * const state;
};

}  // namespace ge

#include <openge/LuaImpl.hpp>
