find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

target_sources(openge PRIVATE
    src/GLShader.cpp
    src/Image.cpp
    src/STBImage.cpp
    src/Window.cpp
)

target_include_directories(openge
    PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    PRIVATE
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/include>"
)

target_link_libraries(openge
    PUBLIC
        glad::glad
        glfw
        stb::stb
)

#=============================
# Install
#=============================
include(GNUInstallDirs)

install(
    DIRECTORY include/
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)
