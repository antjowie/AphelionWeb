#include <emscripten.h>

#include "Engine.hpp"
#include "Log.hpp"
#include "Time.hpp"

// https://emscripten.org/docs/porting/emscripten-runtime-environment.html#browser-main-loop
// We can't have an infinite loop for web browsers since the js code expects to
// return
namespace ap {
void Engine::Run() {
  AP_CORE_INFO("Intializing systems");
  for (auto& system : m_systems) system->Init();

  AP_CORE_INFO("Starting main loop");
  emscripten_set_main_loop(
      []() {
        static Timer time;
        Engine::Get().Loop(time.Reset());
      },
      0, true);
}
}  // namespace ap
