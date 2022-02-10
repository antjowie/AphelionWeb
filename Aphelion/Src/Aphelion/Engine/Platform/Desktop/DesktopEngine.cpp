#include "Aphelion/Core/Time.h"
#include "Aphelion/Engine/Engine.h"

namespace ap
{
void Engine::Run()
{
    Engine& engine = Get();
    engine.InitSystems();

    Timer timer;
    while (!engine.shutdownRequested)
    {
        engine.Loop(timer.Reset());
    }
}
} // namespace ap
