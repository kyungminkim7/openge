#include <gmock/gmock.h>

#include <stdexcept>

#include <openge/Exception.hpp>
#include <openge/Lua.hpp>

using testing::DoubleEq;
using testing::Eq;
using testing::FloatEq;
using testing::HasSubstr;
using testing::IsTrue;
using testing::StrEq;

using ge::BuildError;
using ge::Lua;

class LuaScriptInvalidSyntax : public testing::Test {
 protected:
    static constexpr auto UNFINISHED_STRING_SCRIPT = "var = \"str";
    Lua lua;
};

TEST_F(LuaScriptInvalidSyntax, RaisesException) {
    ASSERT_THROW(
        lua.loadScript(UNFINISHED_STRING_SCRIPT),
        BuildError);
}

TEST_F(LuaScriptInvalidSyntax, ReturnsErrorMessage) {
    try {
        lua.loadScript(UNFINISHED_STRING_SCRIPT);
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
    ASSERT_THROW(
        lua.loadScript(UNINITIALIZED_VAR_SCRIPT),
        std::runtime_error);
}

TEST_F(LuaScriptRuntimeError, ReturnsErrorMessage) {
    try {
        lua.loadScript(UNINITIALIZED_VAR_SCRIPT);
    } catch (const std::runtime_error &e) {
        ASSERT_THAT(e.what(), HasSubstr("nil"));
    }
}

class LuaGetGlobal : public testing::Test {
 protected:
    Lua lua;
};

TEST_F(LuaGetGlobal, String) {
    lua.loadScript("var = \"str\"");

    ASSERT_THAT(lua.getGlobal<std::string>("var"),
                StrEq("str"));
}

TEST_F(LuaGetGlobal, Bool) {
    lua.loadScript("var = true");

    ASSERT_THAT(lua.getGlobal<bool>("var"), IsTrue());
}

TEST_F(LuaGetGlobal, Float) {
    lua.loadScript("var = 3.14");

    ASSERT_THAT(lua.getGlobal<float>("var"), FloatEq(3.14f));
}

TEST_F(LuaGetGlobal, Double) {
    lua.loadScript("var = 3.2489");

    ASSERT_THAT(lua.getGlobal<double>("var"), DoubleEq(3.2489));
}

TEST_F(LuaGetGlobal, Int) {
    lua.loadScript("var = 4");

    ASSERT_THAT(lua.getGlobal<int>("var"), Eq(4));
}

class LuaGetGlobalIncorrectType : public testing::Test {
 protected:
    LuaGetGlobalIncorrectType() {
        lua.loadScript(ASSIGN_NUM_SCRIPT);
    }

    static constexpr auto ASSIGN_NUM_SCRIPT = "x = 3";
    static constexpr auto ASSIGNED_VALUE = "3";
    Lua lua;
};

TEST_F(LuaGetGlobalIncorrectType, RaisesException) {
    ASSERT_THROW(lua.getGlobal<std::string>("x"), std::invalid_argument);
}

TEST_F(LuaGetGlobalIncorrectType, ReturnsErrorMessage) {
    try {
        lua.getGlobal<std::string>("x");
    } catch (const std::invalid_argument &e) {
        ASSERT_THAT(e.what(), HasSubstr(ASSIGNED_VALUE));
    }
}

class LuaSetGlobal : public testing::Test {
 protected:
    LuaSetGlobal() {
        lua.loadScript("var = 0");
    }

    static constexpr auto VAR = "var";
    Lua lua;
};

TEST_F(LuaSetGlobal, CString) {
    const auto VALUE = "str";

    lua.setGlobal(VAR, VALUE);

    ASSERT_THAT(lua.getGlobal<std::string>(VAR), StrEq(VALUE));
}

TEST_F(LuaSetGlobal, String) {
    const std::string VALUE = "str";

    lua.setGlobal(VAR, VALUE);

    ASSERT_THAT(lua.getGlobal<std::string>(VAR), StrEq(VALUE));
}

TEST_F(LuaSetGlobal, Bool) {
    lua.setGlobal(VAR, true);

    ASSERT_THAT(lua.getGlobal<bool>(VAR), IsTrue());
}

TEST_F(LuaSetGlobal, Float) {
    const auto VALUE = 0.43f;

    lua.setGlobal(VAR, VALUE);

    ASSERT_THAT(lua.getGlobal<float>(VAR), FloatEq(VALUE));
}

TEST_F(LuaSetGlobal, Double) {
    const auto VALUE = 0.84;

    lua.setGlobal(VAR, VALUE);

    ASSERT_THAT(lua.getGlobal<double>(VAR), DoubleEq(VALUE));
}

TEST_F(LuaSetGlobal, Int) {
    const auto VALUE = 9;

    lua.setGlobal(VAR, VALUE);

    ASSERT_THAT(lua.getGlobal<int>(VAR), Eq(VALUE));
}