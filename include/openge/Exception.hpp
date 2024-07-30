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
     * Constructs an Error with the given message.
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

/**
 * Represents errors during compilation/linking of shaders/scripts.
 */
class BuildError : public Error {
 public:
    /**
     * Constructs a BuildError with the given message.
     *
     * @param whatArg Explanatory error message.
     */
    explicit BuildError(const std::string &whatArg);
};

}  // namespace ge
