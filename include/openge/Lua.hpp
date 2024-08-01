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

    void execute(std::string_view script) override;

    std::string getGlobalString(std::string_view name) override;

 private:
    void executeChunk();
    std::string popString();

    lua_State * const state;
};

}  // namespace ge
