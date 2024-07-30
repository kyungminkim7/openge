#include <gmock/gmock.h>

#include <stdexcept>
#include <vector>

#include <openge/Exception.hpp>
#include <openge/Lua.hpp>

using testing::ContainerEq;
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
        lua.load(UNFINISHED_STRING_SCRIPT),
        BuildError);
}

TEST_F(LuaScriptInvalidSyntax, ReturnsErrorMessage) {
    try {
        lua.load(UNFINISHED_STRING_SCRIPT);
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
        lua.load(UNINITIALIZED_VAR_SCRIPT),
        std::runtime_error);
}

TEST_F(LuaScriptRuntimeError, ReturnsErrorMessage) {
    try {
        lua.load(UNINITIALIZED_VAR_SCRIPT);
    } catch (const std::runtime_error &e) {
        ASSERT_THAT(e.what(), HasSubstr("nil"));
    }
}

class LuaStackSize : public testing::Test {
 protected:
    LuaStackSize() {
        lua.load("");
    }

    Lua lua;
};

TEST_F(LuaStackSize, IsInitiallyZero) {
    ASSERT_THAT(lua.getStackSize(), Eq(0));
}

TEST_F(LuaStackSize, IncreasesUponPush) {
    lua.push(4);
    ASSERT_THAT(lua.getStackSize(), Eq(1));
}

class LuaGetGlobal : public testing::Test {
 protected:
    Lua lua;
};

TEST_F(LuaGetGlobal, String) {
    lua.load("var = \"str\"");

    ASSERT_THAT(lua.getGlobal<std::string>("var"),
                StrEq("str"));
}

TEST_F(LuaGetGlobal, Bool) {
    lua.load("var = true");

    ASSERT_THAT(lua.getGlobal<bool>("var"), IsTrue());
}

TEST_F(LuaGetGlobal, Float) {
    lua.load("var = 3.14");

    ASSERT_THAT(lua.getGlobal<float>("var"), FloatEq(3.14f));
}

TEST_F(LuaGetGlobal, Double) {
    lua.load("var = 3.2489");

    ASSERT_THAT(lua.getGlobal<double>("var"), DoubleEq(3.2489));
}

TEST_F(LuaGetGlobal, Int) {
    lua.load("var = 4");

    ASSERT_THAT(lua.getGlobal<int>("var"), Eq(4));
}

TEST_F(LuaGetGlobal, CleansTemporaryVariablesFromStack) {
    lua.load("var = 4");

    lua.getGlobal<int>("var");

    ASSERT_THAT(lua.getStackSize(), Eq(0));
}

class LuaGetGlobalIncorrectType : public testing::Test {
 protected:
    LuaGetGlobalIncorrectType() {
        lua.load(ASSIGN_NUM_SCRIPT);
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

TEST_F(LuaGetGlobalIncorrectType, CleansTemporaryVariablesFromStack) {
    try {
        lua.getGlobal<std::string>("x");
    } catch (const std::invalid_argument &) {
        ASSERT_THAT(lua.getStackSize(), Eq(0));
    }
}

class LuaSetGlobal : public testing::Test {
 protected:
    LuaSetGlobal() {
        lua.load("var = 0");
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

TEST_F(LuaSetGlobal, CleansTemporaryVariablesFromStack) {
    lua.setGlobal(VAR, 4);
    ASSERT_THAT(lua.getStackSize(), Eq(0));
}

TEST(LuaStandardLibraries, AreLoaded) {
    Lua lua;
    lua.load("var = tostring(4)");

    ASSERT_THAT(lua.getGlobal<std::string>("var"),
                StrEq("4"));
}

class LuaCall : public testing::Test {
 protected:
    Lua lua;
};

TEST_F(LuaCall, FunctionWithNoParameters) {
    lua.load("function fxn()\n"
             "    return \"out\"\n"
             "end");

    ASSERT_THAT(lua.call<std::string>("fxn"), StrEq("out"));
}

TEST_F(LuaCall, CleansTemporaryVariablesFromStack) {
    lua.load("function fxn()\n"
             "    return \"out\"\n"
             "end");

    ASSERT_THAT(lua.getStackSize(), Eq(0));
}

TEST_F(LuaCall, NonFunctionVariableThrowsErrors) {
    lua.load("fxn = 4");

    ASSERT_THROW(lua.call<int>("fxn"), std::invalid_argument);
}

TEST_F(LuaCall, ErrorMaintainsStackSize) {
    try {
        lua.load("fxn = 4");
    } catch (const std::invalid_argument &) {
        ASSERT_THAT(lua.getStackSize(), Eq(0));
    }
}

TEST_F(LuaCall, FunctionWithParameters) {
    lua.load("function add(str, n)\n"
             "    return str..\": \"..tostring(n)\n"
             "end");

    ASSERT_THAT(lua.call<std::string>("add", "PI", 3.14),
                StrEq("PI: 3.14"));
}

TEST_F(LuaCall, FunctionReturningMultipleValues) {
    lua.load("function fxn()\n"
             "    return 1, 2, 3\n"
             "end");

    ASSERT_THAT(lua.call<std::vector<int>>("fxn"),
                ContainerEq(std::vector<int>{1, 2, 3}));
}

class LuaGetTableEntry : public testing::Test {
 protected:
    LuaGetTableEntry() {
        lua.load("position = { x = 1, y = 2 }");
    }

    constexpr static auto TABLE = "position";
    constexpr static auto KEY = "x";
    constexpr static auto VALUE = 1;

    Lua lua;
};

TEST_F(LuaGetTableEntry, ReturnsValue) {
    ASSERT_THAT(lua.getTableEntry<int>(TABLE, KEY),
                Eq(VALUE));
}

TEST_F(LuaGetTableEntry, CleansTemporaryVariablesFromStack) {
    lua.getTableEntry<int>(TABLE, KEY);

    ASSERT_THAT(lua.getStackSize(), Eq(0));
}

class LuaGetInvalidTable : public testing::Test {
 protected:
    LuaGetInvalidTable() {
        lua.load("position = 2");
    }

    static constexpr auto INVALID_TABLE = "position";
    static constexpr auto INVALID_KEY = "key";

    Lua lua;
};

TEST_F(LuaGetInvalidTable, RaisesException) {
    ASSERT_THROW(lua.getTableEntry<int>(INVALID_TABLE, INVALID_KEY),
                 std::invalid_argument);
}

TEST_F(LuaGetInvalidTable, ErrorMaintainsStackSize) {
    try {
        lua.getTableEntry<int>(INVALID_TABLE, INVALID_KEY);
    } catch (const std::invalid_argument &) {
        ASSERT_THAT(lua.getStackSize(), Eq(0));
    }
}

class LuaSetTableEntry : public testing::Test {
 protected:
    LuaSetTableEntry() {
        lua.load("position = { x = 0 }");

        lua.setTableEntry(TABLE, KEY, VALUE);
    }

    constexpr static auto TABLE = "position";
    constexpr static auto KEY = "x";
    constexpr static auto VALUE = 4.2;

    Lua lua;
};

TEST_F(LuaSetTableEntry, SetsValue) {
    ASSERT_THAT(lua.getTableEntry<double>(TABLE, KEY),
                DoubleEq(VALUE));
}

TEST_F(LuaSetTableEntry, CleansTemporaryVariablesFromStack) {
    ASSERT_THAT(lua.getStackSize(), Eq(0));
}

class LuaGetArrayElement : public testing::Test {
 protected:
    LuaGetArrayElement() {
        lua.load("array = { 4, 5, 6 }");
    }

    constexpr static auto ARRAY = "array";
    constexpr static auto INDEX = 2;
    constexpr static auto VALUE = 5;

    Lua lua;
};

TEST_F(LuaGetArrayElement, ReturnsValue) {
    ASSERT_THAT(lua.getTableEntry<int>(ARRAY, INDEX), Eq(VALUE));
}

TEST_F(LuaGetArrayElement, CleansTemporaryVariablesFromStack) {
    lua.getTableEntry<int>(ARRAY, INDEX);

    ASSERT_THAT(lua.getStackSize(), Eq(0));
}

TEST_F(LuaGetArrayElement, ThrowsOnZeroIndex) {
    ASSERT_THROW(lua.getTableEntry<int>(ARRAY, 0),
                 std::out_of_range);
}

class LuaSetArrayElement : public testing::Test {
 protected:
    LuaSetArrayElement() {
        lua.load("array = { 4, 5, 6 }");
    }

    constexpr static auto ARRAY = "array";
    constexpr static auto INDEX = 1;
    constexpr static auto VALUE = 8;

    Lua lua;
};

TEST_F(LuaSetArrayElement, UpdatesValue) {
    lua.setTableEntry(ARRAY, INDEX, VALUE);

    ASSERT_THAT(lua.getTableEntry<int>(ARRAY, INDEX), Eq(VALUE));
}

TEST_F(LuaSetArrayElement, CleansTemporaryVariablesFromStack) {
    lua.setTableEntry(ARRAY, INDEX, VALUE);

    ASSERT_THAT(lua.getStackSize(), Eq(0));
}

TEST_F(LuaSetArrayElement, ThrowsOnZeroIndex) {
    ASSERT_THROW(lua.setTableEntry<int>(ARRAY, 0, VALUE),
                 std::out_of_range);
}
