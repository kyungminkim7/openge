#pragma once

#include <ostream>

#include <glm/fwd.hpp>
#include <glm/gtx/string_cast.hpp>

namespace glm {

template<length_t L, typename T, qualifier Q>
std::ostream & operator<<(std::ostream &os, const vec<L, T, Q> &v) {
    return os << to_string(v);
}

}  // namespace glm
