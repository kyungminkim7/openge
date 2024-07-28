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
     * Get the value of a global string variable in the script.
     *
     * @param name Global variable name.
     * @return Global variable value.
     */
    virtual std::string getGlobalString(std::string_view name) = 0;
};

}  // namespace ge
