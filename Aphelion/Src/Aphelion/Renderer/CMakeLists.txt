# cmake_minimum_required(VERSION 3.18)

# add_library(Renderer
#     # Renderer.hpp
# )

# add_library(Aphelion::Renderer ALIAS Renderer)

# # target_precompile_headers(Physics REUSE_FROM Aphelion::Core)
# get_target_property(CORE_PCH Aphelion::Core PRECOMPILE_HEADERS)
# target_precompile_headers(
#     Renderer
#     PUBLIC
#     ${CORE_PCH}
# )

# target_include_directories(Core PUBLIC ../../)