cmake_minimum_required(VERSION 3.16)

add_library(ImGui
    $<$<PLATFORM_ID:Windows,Linux>:
        Platform/Desktop/DesktopImGui.cpp
        Platform/Desktop/DesktopImGui.h
    >

    $<$<PLATFORM_ID:Emscripten>:
        Platform/Web/WebImGui.cpp
        Platform/Web/WebImGui.h
    >

    ImGuiSystem.h
)
add_library(Aphelion::ImGui ALIAS ImGui)

target_precompile_headers(ImGui REUSE_FROM Aphelion::Core)

target_include_directories(ImGui PRIVATE ./)

CPMAddPackage(
    NAME DearImGui
    GIT_REPOSITORY https://github.com/ocornut/imgui
    GIT_TAG 1e14cc5cae703b7cdf0e33c50165d6dd289fcb1f
    DOWNLOAD_ONLY YES
)

if (DearImGui_ADDED)
    # FILE(GLOB DearImGui_sources ${DearImGui_SOURCE_DIR}/*.cpp)
    add_library(DearImGui STATIC
        $<$<PLATFORM_ID:Windows,Linux>:
            ${DearImGui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
            ${DearImGui_SOURCE_DIR}/backends/imgui_impl_opengl3.h
            ${DearImGui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
            ${DearImGui_SOURCE_DIR}/backends/imgui_impl_glfw.h
        >

        $<$<PLATFORM_ID:Emscripten>:
            ${DearImGui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
            ${DearImGui_SOURCE_DIR}/backends/imgui_impl_opengl3.h
            ${DearImGui_SOURCE_DIR}/backends/imgui_impl_sdl.cpp
            ${DearImGui_SOURCE_DIR}/backends/imgui_impl_sdl.h
        >

        ${DearImGui_SOURCE_DIR}/imconfig.h
        ${DearImGui_SOURCE_DIR}/imgui.cpp
        ${DearImGui_SOURCE_DIR}/imgui.h
        ${DearImGui_SOURCE_DIR}/imgui_demo.cpp
        ${DearImGui_SOURCE_DIR}/imgui_draw.cpp
        ${DearImGui_SOURCE_DIR}/imgui_internal.h
        ${DearImGui_SOURCE_DIR}/imgui_tables.cpp
        ${DearImGui_SOURCE_DIR}/imgui_widgets.cpp
        ${DearImGui_SOURCE_DIR}/imstb_rectpack.h
        ${DearImGui_SOURCE_DIR}/imstb_textedit.h
        ${DearImGui_SOURCE_DIR}/imstb_truetype.h
    )

    target_include_directories(DearImGui PUBLIC
        ${DearImGui_SOURCE_DIR}/.
    )

    target_link_libraries(DearImGui PUBLIC Aphelion::Window)
else()
    message(FATAL_ERROR "Could not create a target from Dear ImGui")
endif()

target_link_libraries(ImGui
PUBLIC
    Aphelion::Core
    Aphelion::Window
    DearImGui
)
