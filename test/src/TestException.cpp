#include <gmock/gmock.h>

#include <openge/Exception.hpp>

using testing::StrEq;

TEST(ExceptionWhat, ReturnsErrorMessage) {
  constexpr auto ERROR_MSG = "Build failed";
  try {
    throw ge::Error(ERROR_MSG);
  } catch (const ge::Error& e) {
    ASSERT_THAT(e.what(), StrEq(ERROR_MSG));
  }
}
