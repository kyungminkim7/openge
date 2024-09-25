target_sources(openge PRIVATE
    src/Asset.cpp
    src/AssetManager.cpp
    src/GLBuffer.cpp
    src/GLFunctions.cpp
    src/GLShader.cpp
    src/GLShaderProgram.cpp
    src/GLVertexArrayObject.cpp
    src/Log.cpp
)

target_include_directories(openge PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
)

target_link_libraries(openge
    PUBLIC
        android
        GLESv3
    PRIVATE
        EGL
        log
)

#=============================
# Install
#=============================
include(GNUInstallDirs)

install(
    DIRECTORY include/
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)