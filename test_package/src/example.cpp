#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include <openge/CoordinateSystem.hpp>

int main() {
  std::cout << "OpenGE coordinate system:\n"
            << "FORWARD: " << glm::to_string(ge::CoordinateSystem::FORWARD)
            << '\n'

            << "LEFT   : " << glm::to_string(ge::CoordinateSystem::LEFT) << '\n'

            << "UP     : " << glm::to_string(ge::CoordinateSystem::UP) << '\n';

  return 0;
}
