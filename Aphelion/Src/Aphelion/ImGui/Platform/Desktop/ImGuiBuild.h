// Required for building ImGui as it's own DLL so that there is
// one place that the globals are accessed to
#include "Aphelion/Core/Core.h"
#define IMGUI_API APHELION_API
