#include "Engine.h"
#include "Time.h"

namespace ap
{
void Engine::Run()
{
    Init();

    Timer timer;
    while(true)
    {
        Loop(timer.Reset());
    }
}
} // namespace ap
