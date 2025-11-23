#include <string>

#include <openge/Exception.hpp>

namespace ge {

Error::Error(const std::string &whatArg) : whatArg(whatArg) {}

const char * Error::what() const noexcept {
    return whatArg.c_str();
}

BuildError::BuildError(const std::string &whatArg) : Error(whatArg) {}

LoadError::LoadError(const std::string &whatArg) : Error(whatArg) {}

WindowError::WindowError(const std::string &whatArg) : Error(whatArg) {}

}  // namespace ge
