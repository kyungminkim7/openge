#pragma once

#include <string>
#include <string_view>

namespace ge {

/**
 * Interface for embedded scripting.
 */
class ScriptingEngineInterface {
 public:
    virtual ~ScriptingEngineInterface() = default;

    /**
     * Compiles and executes the given string as an embedded script.
     * 
     * @param script Inline script code to load and execute.
     */
    virtual void execute(std::string_view script) = 0;

    /**
     * Get the value of a global string variable in the script.
     *
     * @param name Global variable name.
     * @return Global variable value.
     */
    virtual std::string getGlobalString(std::string_view name) = 0;
};

}  // namespace ge
