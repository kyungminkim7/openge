#pragma once

#include <string>

namespace ge {
namespace Log {

void verbose(const std::string &msg);
void debug(const std::string &msg);
void info(const std::string &msg);
void warn(const std::string &msg);
void error(const std::string &msg);
void fatal(const std::string &msg);

}  // namespace Log
}  // namespace ge
