cmake_minimum_required(VERSION 3.18)

add_library(Renderer
  Renderer.cpp
  Renderer.h
)

add_library(Aphelion::Renderer ALIAS Renderer)
target_link_libraries(Renderer PUBLIC Aphelion::Core)
