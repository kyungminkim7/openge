target_sources(
  openge
  PRIVATE src/Asset.cpp
          src/AssetManager.cpp
          src/AssimpIOStream.cpp
          src/AssimpIOSystem.cpp
          src/GLShader.cpp
          src/Image.cpp
          src/ImageDecoder.cpp
          src/Log.cpp)

target_include_directories(
  openge
  PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
  PRIVATE "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/include>")

target_link_libraries(
  openge
  PUBLIC android GLESv3
  PRIVATE log)

# =============================
# Install
# =============================
include(GNUInstallDirs)

install(DIRECTORY include/ DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")
