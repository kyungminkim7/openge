#include <gmock/gmock.h>

#include <stdexcept>

#include <openge/Exception.hpp>
#include <openge/Lua.hpp>

using testing::HasSubstr;
using testing::StrEq;
using ge::BuildError;
using ge::Lua;

class LuaScriptInvalidSyntax : public testing::Test {
 protected:
    static constexpr auto UNFINISHED_STRING_SCRIPT = "var = \"str";
    Lua lua;
};

TEST_F(LuaScriptInvalidSyntax, RaisesException) {
    ASSERT_THROW(lua.execute(LuaScriptInvalidSyntax::UNFINISHED_STRING_SCRIPT),
                 BuildError);
}

TEST_F(LuaScriptInvalidSyntax, ReturnsErrorMessage) {
    try {
        lua.execute(LuaScriptInvalidSyntax::UNFINISHED_STRING_SCRIPT);
        FAIL() << "Invalid script failed to throw build error";
    } catch (const BuildError &e) {
        ASSERT_THAT(e.what(), HasSubstr("unfinished string"));
    }
}

class LuaScriptRuntimeError : public testing::Test {
 protected:
    static constexpr auto UNINITIALIZED_VAR_SCRIPT = "print(a / 2)";
    Lua lua;
};

TEST_F(LuaScriptRuntimeError, RaisesException) {
    ASSERT_THROW(lua.execute(LuaScriptRuntimeError::UNINITIALIZED_VAR_SCRIPT),
                 std::runtime_error);
}

TEST_F(LuaScriptRuntimeError, ReturnsErrorMessage) {
    try {
        lua.execute(LuaScriptRuntimeError::UNINITIALIZED_VAR_SCRIPT);
        FAIL() << "Invalid script failed to throw runtime error";
    } catch (const std::runtime_error &e) {
        ASSERT_THAT(e.what(), HasSubstr("nil"));
    }
}

TEST(LuaGetGlobalString, ReturnsValueSetInScript) {
    Lua lua;
    lua.execute("var = \"str\"");

    ASSERT_THAT(lua.getGlobalString("var"),
                StrEq("str"));
}

class LuaGetGlobalStringIncorrectType : public testing::Test {
 protected:
    LuaGetGlobalStringIncorrectType() {
        lua.execute(LuaGetGlobalStringIncorrectType::ASSIGN_NUM_SCRIPT);
    }

    static constexpr auto ASSIGN_NUM_SCRIPT = "x = 3";
    static constexpr auto ASSIGNED_VALUE = "3";
    Lua lua;
};

TEST_F(LuaGetGlobalStringIncorrectType, RaisesException) {
    ASSERT_THROW(lua.getGlobalString("x"), std::invalid_argument);
}

TEST_F(LuaGetGlobalStringIncorrectType, ReturnsErrorMessage) {
    try {
        lua.getGlobalString("x");
    } catch (const std::invalid_argument &e) {
        ASSERT_THAT(e.what(),
                    HasSubstr(LuaGetGlobalStringIncorrectType::ASSIGNED_VALUE));
    }
}
