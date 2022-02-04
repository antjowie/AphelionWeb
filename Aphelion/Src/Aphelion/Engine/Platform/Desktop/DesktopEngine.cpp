#include "Engine.hpp"
#include "Time.hpp"

namespace ap {
void Engine::Run() {
  Init();

  Timer timer;
  while (true) {
    Loop(timer.Reset());
  }
}
}  // namespace ap
