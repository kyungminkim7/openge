find_package(GTest REQUIRED CONFIG)
include(GoogleTest)

add_executable(openge_test
    src/TestException.cpp
    src/TestLua.cpp
)

target_link_libraries(openge_test
    openge
    GTest::gmock
    GTest::gtest
    GTest::gtest_main
)

gtest_discover_tests(openge_test)