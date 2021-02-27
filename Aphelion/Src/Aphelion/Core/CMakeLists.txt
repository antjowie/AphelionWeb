cmake_minimum_required(VERSION 3.18)

option(APHELION_FORCE_ASSERT false)

add_library(Core
    Core.hpp
    Engine.cpp
    Engine.hpp
    Helper.hpp
    Log.cpp
    Log.hpp
    System.hpp
    Time.hpp
)

add_library(Aphelion::Core ALIAS Core)

CPMAddPackage(gh:gabime/spdlog@1.8.2)

target_link_libraries(Core PUBLIC
    spdlog::spdlog
)

target_precompile_headers(Core
    PRIVATE
    <iostream>
    <memory>
    <utility>
    <algorithm>
    <functional>
    <string>
    <sstream>
    <array>
    <vector>
    <unordered_map>
    <unordered_set>
    <type_traits>

    # <glm/vec3.hpp>
    # <glm/mat4x4.hpp>
    # <glm/gtc/quaternion.hpp>
    # <glm/gtc/matrix_transform.hpp>
    # <glm/gtc/matrix_transform.hpp>
    # <glm/gtc/type_ptr.hpp>
    # <glm/gtx/quaternion.hpp>
    # <glm/gtx/hash.hpp>

    Core.hpp
    Log.hpp
)

target_include_directories(Core PUBLIC ../../)

target_compile_definitions(Core 
    PUBLIC 
    $<$<BOOL:${APHELION_FORCE_ASSERT}>:FORCE_ASSERT>
    $<$<STREQUAL:${CMAKE_BUILD_TYPE},Debug>:AP_DEBUG>
    $<$<BOOL:${BUILD_SHARED_LIBS}>:AP_DYNAMIC_LINK>
    PRIVATE
    $<$<BOOL:${BUILD_SHARED_LIBS}>:AP_BUILD_DLL>
)
