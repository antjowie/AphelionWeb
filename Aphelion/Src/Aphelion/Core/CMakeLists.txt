cmake_minimum_required(VERSION 3.21)

option(APHELION_FORCE_ASSERT "Force asserts even in release" false)

add_library(Core

    Event/Event.h
    Event/KeyEvent.h
    Event/MouseEvent.h
    Event/WindowEvent.h

    # Input/Input.h
    # Input/Input.cpp
    Input/KeyCodes.h
    Input/MouseCodes.h

    Core.cpp
    Core.h
    Util.h
    Log.cpp
    Log.h
    System.h
    Time.h
)
add_library(Aphelion::Core ALIAS Core)

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
    <chrono>

    # <glm/vec3.hpp>
    # <glm/mat4x4.hpp>
    # <glm/gtc/quaternion.hpp>
    # <glm/gtc/matrix_transform.hpp>
    # <glm/gtc/matrix_transform.hpp>
    # <glm/gtc/type_ptr.hpp>
    # <glm/gtx/quaternion.hpp>
    # <glm/gtx/hash.hpp>

    Core.h
    Log.h
)

target_include_directories(Core
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../../
# For some reason, MSVC breaks down if I try to add local dir
# PRIVATE
#     ${CMAKE_CURRENT_SOURCE_DIR}/.
)

CPMAddPackage(gh:gabime/spdlog@1.8.2)
target_link_libraries(Core PUBLIC
    spdlog::spdlog
)

target_compile_definitions(Core
PUBLIC
    $<$<BOOL:${APHELION_FORCE_ASSERT}>:AP_FORCE_ASSERT>
    $<$<STREQUAL:${CMAKE_BUILD_TYPE},Debug>:AP_DEBUG>
    $<$<BOOL:${BUILD_SHARED_LIBS}>:AP_DYNAMIC_LINK>
)
