#include "Aphelion/Core/Time.h"
#include "Aphelion/Engine/Engine.h"

namespace ap
{
void Engine::Run()
{
    Init();

    Timer timer;
    while (true)
    {
        Loop(timer.Reset());
    }
}
} // namespace ap
