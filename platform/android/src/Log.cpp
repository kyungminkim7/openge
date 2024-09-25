#include <android/log.h>

#include <ios>
#include <system_error>

#include <openge/Log.hpp>

namespace {

constexpr auto TAG = "openge";

void print(int priority, const std::string &msg) {
    if (__android_log_print(priority, TAG, "%s\n", msg.c_str()) == -EPERM) {
        const auto errorCode =
            std::make_error_code(std::errc::operation_not_permitted);
        throw std::system_error(errorCode, "Failed to print log");
    }
}

}  // namespace

namespace ge {
namespace Log {

void verbose(const std::string &msg) {
    print(ANDROID_LOG_VERBOSE, msg);
}

void debug(const std::string &msg) {
    print(ANDROID_LOG_DEBUG, msg);
}

void info(const std::string &msg) {
    print(ANDROID_LOG_INFO, msg);
}

void warn(const std::string &msg) {
    print(ANDROID_LOG_WARN, msg);
}

void error(const std::string &msg) {
    print(ANDROID_LOG_ERROR, msg);
}

void fatal(const std::string &msg) {
    print(ANDROID_LOG_FATAL, msg);
}

}  // namespace Log
}  // namespace ge
