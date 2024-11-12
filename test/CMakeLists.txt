find_package(GTest REQUIRED CONFIG)
include(GoogleTest)

add_executable(openge_test
    src/TestException.cpp
    src/TestGameObject.cpp
    src/TestInputSystem.cpp
    src/TestTransform.cpp
)

target_include_directories(openge_test PRIVATE
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
)

target_compile_definitions(openge_test PRIVATE
    GLM_ENABLE_EXPERIMENTAL
)

target_link_libraries(openge_test
    openge
    GTest::gmock
    GTest::gtest
    GTest::gtest_main
)

gtest_discover_tests(openge_test)