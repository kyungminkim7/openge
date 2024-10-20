cmake_minimum_required(VERSION 3.15)
project(PackageTest CXX)

find_package(openge CONFIG REQUIRED)

add_executable(example src/example.cpp)

target_compile_definitions(example PRIVATE
    GLM_ENABLE_EXPERIMENTAL
)

target_link_libraries(example openge::openge)
