cmake_minimum_required(VERSION 3.15)
project(openge CXX)

#=============================
# Static Analysis
#=============================
set(CMAKE_CXX_CPPCHECK "cppcheck;--error-exitcode=1;--enable=performance,portability;--quiet")

#=============================
# Build
#=============================
find_package(glm CONFIG REQUIRED)
find_package(lua CONFIG REQUIRED)

add_library(openge
    src/Exception.cpp
    src/Lua.cpp
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
