cmake_minimum_required(VERSION 3.15)
project(openge CXX)

#=============================
# Static Analysis
#=============================
set(CMAKE_CXX_CPPCHECK
    "cppcheck;--error-exitcode=1;--inline-suppr;--enable=performance,portability")

#=============================
# Build
#=============================
find_package(glm CONFIG REQUIRED)
find_package(lua CONFIG REQUIRED)

# Configure built-in shaders
if(CMAKE_SYSTEM_NAME STREQUAL "Android")
    set(GLSL_VERSION "320 es")

    string(JOIN "\n" GLSL_PRECISION
           "precision mediump float;"
           "precision mediump sampler2DShadow;")
else()
    set(GLSL_VERSION "330 core")
endif()

configure_file(shader/Standard.frag.in
               shader/Standard.frag)

configure_file(shader/Standard.vert.in
               shader/Standard.vert)

file(READ "${CMAKE_CURRENT_BINARY_DIR}/shader/Standard.frag" STANDARD_FRAG)
file(READ "${CMAKE_CURRENT_BINARY_DIR}/shader/Standard.vert" STANDARD_VERT)

configure_file(src/RenderPipeline.cpp.in
               src/RenderPipeline.cpp)

# OpenGE library
add_library(openge
    "${CMAKE_CURRENT_BINARY_DIR}/src/RenderPipeline.cpp"
    src/Camera.cpp
    src/ColorConstants.cpp
    src/Component.cpp
    src/CoordinateSystem.cpp
    src/Exception.cpp
    src/GameObject.cpp
    src/InputSystem.cpp
    src/Lua.cpp
    src/Material.cpp
    src/Mesh.cpp
    src/Transform.cpp
)

target_include_directories(openge PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
)

target_link_libraries(openge
    PUBLIC
        glm::glm
        lua::lua
)

add_subdirectory(platform)

#=============================
# Test
#=============================
if(NOT CMAKE_SYSTEM_NAME STREQUAL "Android")
    enable_testing()
    add_subdirectory(test)
endif()

#=============================
# Documentation
#=============================
find_package(Doxygen)

set(DOXYGEN_QUIET YES)
set(DOXYGEN_USE_MDFILE_AS_MAINPAGE README.md)
set(DOXYGEN_WARN_AS_ERROR YES)

set(DOXYGEN_EXCLUDE
    build
    conanfile.py
    mock
    test
    test_package
)

doxygen_add_docs(generate_docs
    "${CMAKE_CURRENT_LIST_DIR}"
    ALL
    COMMENT "Generating Doxygen documentation..."
)

#=============================
# Install
#=============================
include(GNUInstallDirs)

install(TARGETS openge)

install(
    DIRECTORY include/
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)
