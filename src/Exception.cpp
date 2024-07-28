#include <openge/Exception.hpp>

namespace ge {

Error::Error(const std::string &whatArg) : whatArg(whatArg) {}

const char * Error::what() const noexcept {
    return whatArg.c_str();
}

}  // namespace ge
