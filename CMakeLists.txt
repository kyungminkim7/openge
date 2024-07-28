cmake_minimum_required(VERSION 3.15)
project(openge CXX)

#=============================
# Static Analysis
#=============================
set(CMAKE_CXX_CPPCHECK "cppcheck;--error-exitcode=1;--enable=style")

#=============================
# Build
#=============================
find_package(lua CONFIG REQUIRED)

add_library(openge
    src/Exception.cpp
    src/Lua.cpp
)

target_include_directories(openge PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
)

target_link_libraries(openge
    PRIVATE
        lua::lua
)

add_subdirectory(platform)

#=============================
# Test
#=============================
enable_testing()
add_subdirectory(test)

#=============================
# Documentation
#=============================
find_package(Doxygen)

set(DOXYGEN_AUTOLINK_SUPPORT YES)
set(DOXYGEN_CALL_GRAPH YES)
set(DOXYGEN_CLASS_GRAPH YES)
set(DOXYGEN_COLLABORATION_GRAPH YES)
set(DOXYGEN_DOT_UML_DETAILS YES)
set(DOXYGEN_DOT_WRAP_THRESHOLD 100)
set(DOXYGEN_GENERATE_HTML YES)
set(DOXYGEN_MARKDOWN_SUPPORT YES)
set(DOXYGEN_QUIET YES)
set(DOXYGEN_UML_LOOK YES)
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
    DIRECTORY include/ mock/
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)
