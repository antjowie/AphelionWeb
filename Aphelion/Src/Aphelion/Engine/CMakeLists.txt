cmake_minimum_required(VERSION 3.18)

option(APHELION_FORCE_ASSERT false)

add_library(Engine
  Engine.cpp
  Engine.hpp
  
  $<$<PLATFORM_ID:Windows>:
    Platform/Desktop/DesktopEngine.cpp
  >

  $<$<PLATFORM_ID:Emscripten>:
    Platform/Web/WebEngine.cpp
  >
)
add_library(Aphelion::Engine ALIAS Engine)

target_include_directories(Engine PRIVATE ./)
target_link_libraries(Engine  
  PUBLIC 
    Aphelion::Core 
    Aphelion::Window 
    # Aphelion::ImGUI
)
