cmake_minimum_required(VERSION 3.18)

add_library(ImGUI
  $<$<PLATFORM_ID:Emscripten>:
    Platform/Web/WebImGUI.cpp
    Platform/Web/WebImGUI.hpp
  >
  
  ImGUI.hpp
)
add_library(Aphelion::ImGUI ALIAS ImGUI)

CPMAddPackage(
  NAME DearImGUI
  GIT_REPOSITORY https://github.com/ocornut/imgui 
  GIT_TAG 732cd837a9ed8ecb2ce4035e7d40a1c9a04ae240
  DOWNLOAD_ONLY YES
)

if (DearImGUI_ADDED)
  # FILE(GLOB DearImGUI_sources ${DearImGUI_SOURCE_DIR}/*.cpp)
  add_library(DearImGUI STATIC 
    ${DearImGUI_SOURCE_DIR}/imconfig.h
    ${DearImGUI_SOURCE_DIR}/imgui.cpp
    ${DearImGUI_SOURCE_DIR}/imgui.h
    ${DearImGUI_SOURCE_DIR}/imgui_demo.cpp
    ${DearImGUI_SOURCE_DIR}/imgui_draw.cpp
    ${DearImGUI_SOURCE_DIR}/imgui_internal.h
    ${DearImGUI_SOURCE_DIR}/imgui_tables.cpp
    ${DearImGUI_SOURCE_DIR}/imgui_widgets.cpp
    ${DearImGUI_SOURCE_DIR}/imstb_rectpack.h
    ${DearImGUI_SOURCE_DIR}/imstb_textedit.h
    ${DearImGUI_SOURCE_DIR}/imstb_truetype.h
    
    ${DearImGUI_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
    ${DearImGUI_SOURCE_DIR}/backends/imgui_impl_opengl3.h
    ${DearImGUI_SOURCE_DIR}/backends/imgui_impl_sdl.cpp
    ${DearImGUI_SOURCE_DIR}/backends/imgui_impl_sdl.h
  )

  target_include_directories(DearImGUI PUBLIC
    ${DearImGUI_SOURCE_DIR}/.
    ${DearImGUI_SOURCE_DIR}/backends/.
  )
else()
  message(FATAL_ERROR "Could not create a target from Dear ImGUI")
endif()

target_include_directories(ImGUI PRIVATE ./)
target_link_libraries(ImGUI 
  PUBLIC Aphelion::Core DearImGUI 
  PRIVATE Aphelion::Window
)