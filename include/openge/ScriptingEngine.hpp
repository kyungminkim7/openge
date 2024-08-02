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

    /**
     * Set the value of a global string variable in the script.
     *
     * @param name Name of the global variable to set.
     * @param value Value to set the global variable to.
     */
    virtual void setGlobal(std::string_view name,
                           std::string_view value) = 0;
};

}  // namespace ge
