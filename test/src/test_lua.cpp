#include <gmock/gmock.h>

#include <openge/Lua.hpp>

using testing::StrEq;
using ge::Lua;

TEST(LuaGetGlobal, ReturnsValueSetInScript) {
    Lua lua;
    lua.loadScript("var = \"str\"");

    ASSERT_THAT(lua.getGlobalString("var"),
                StrEq("str"));
}
