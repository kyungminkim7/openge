#pragma once

#include <cstddef>

namespace ge::AssimpIOSystem {

/**
* Returns a nullptr for Assimp to use the default IOSystem.
*
* @return nullptr.
*/
std::nullptr_t create() { return nullptr; }

}  // namespace ge::AssimpIOSystem
