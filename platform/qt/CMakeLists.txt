find_package(Qt6 REQUIRED COMPONENTS OpenGL)

target_sources(openge PRIVATE
    src/GLShaderProgram.cpp
)

target_include_directories(openge PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
)

target_link_libraries(openge PUBLIC
    Qt6::Gui
    Qt6::OpenGL
)

#=============================
# Install
#=============================
include(GNUInstallDirs)

install(
    DIRECTORY include/
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)