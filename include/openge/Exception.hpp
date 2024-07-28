#pragma once

#include <exception>
#include <string>

namespace ge {

/**
 * Base class for exceptions/errors.
 */
class Error : public std::exception {
 public:
    /**
     * Constructs a new Error with the given message.
     *
     * @param whatArg Explanatory error message.
     */
    explicit Error(const std::string &whatArg);

    /**
     * Returns the explanatory error message.
     * 
     * @return Explanatory error message.
     */
    const char * what() const noexcept override;

 private:
    std::string whatArg;
};

}  // namespace ge
