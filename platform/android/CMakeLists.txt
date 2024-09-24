MESSAGE("GOING ANDROID PLATFORM")

target_sources(openge PRIVATE
    src/GLFunctions.cpp
)

target_include_directories(openge PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
)

target_link_libraries(openge PUBLIC
    GLESv3
)

#=============================
# Install
#=============================
include(GNUInstallDirs)

install(
    DIRECTORY include/
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)