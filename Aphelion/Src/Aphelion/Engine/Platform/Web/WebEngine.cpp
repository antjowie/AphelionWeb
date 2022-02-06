#include "Aphelion/Core/Log.h"
#include "Aphelion/Core/Time.h"
#include "Engine.h"

#include <emscripten.h>

// https://emscripten.org/docs/porting/emscripten-runtime-environment.html#browser-main-loop
// We can't have an infinite loop for web browsers since the js code expects to
// return
namespace ap
{
void Engine::Run()
{
    Init();

    AP_CORE_INFO("Starting main loop");
    emscripten_set_main_loop(
        []() {
            static Timer time;
            Engine::Get().Loop(time.Reset());
        },
        0, true);
}
} // namespace ap
