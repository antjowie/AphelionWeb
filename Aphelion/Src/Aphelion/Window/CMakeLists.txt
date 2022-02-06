cmake_minimum_required(VERSION 3.18)

add_library(Window
    $<$<PLATFORM_ID:Windows,Linux>:
        Platform/Desktop/DesktopWindow.cpp
        Platform/Desktop/DesktopWindow.h
    >

    $<$<PLATFORM_ID:Emscripten>:
        Platform/Web/WebWindow.cpp
        Platform/Web/WebWindow.h
    >

    Window.h
)
add_library(Aphelion::Window ALIAS Window)

target_precompile_headers(Window PRIVATE ${APHELION_PCH})

# Check desktop platform for glfw and glad
if(CMAKE_SYSTEM_NAME STREQUAL Windows OR CMAKE_SYSTEM_NAME STREQUAL Linux)
    add_library(glad
        ThirdParty/glad/include/glad/gl.h
        ThirdParty/glad/include/KHR/khrplatform.h
        ThirdParty/glad/src/gl.c
    )

    target_include_directories(glad PUBLIC ThirdParty/glad/include)

    option(GLFW_STANDALONE OFF)
    option(GLFW_BUILD_EXAMPLES "Build the GLFW example programs" ${GLFW_STANDALONE})
    option(GLFW_BUILD_TESTS "Build the GLFW test programs" ${GLFW_STANDALONE})
    option(GLFW_BUILD_DOCS "Build the GLFW documentation" ON)
    option(GLFW_INSTALL "Generate installation target" ON)
    CPMAddPackage("gh:glfw/glfw#3.3.6")

    target_link_libraries(Window PUBLIC
        glad
        glfw
    )
endif()

target_link_libraries(Window PUBLIC Aphelion::Core)
