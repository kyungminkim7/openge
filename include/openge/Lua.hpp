#pragma once

#include <string>

#include <openge/ScriptingEngine.hpp>

struct lua_State;

namespace ge {

/**
 * Scripting engine for executing Lua scripts.
 */
class Lua : public ScriptingEngineInterface {
 public:
    Lua();
    ~Lua() override;

    /**
     * Loads and compiles the given string as an embedded script.
     * 
     * @param script Inline script code to load and execute.
     */
    void loadScript(std::string_view script);

    std::string getGlobalString(std::string_view name) override;

 private:
    std::string popString();

    lua_State * const state;
};

}  // namespace ge
