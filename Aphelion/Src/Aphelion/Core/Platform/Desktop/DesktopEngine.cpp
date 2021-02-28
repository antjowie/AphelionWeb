#include "Engine.hpp"
#include "Time.hpp"

namespace ap
{   
    void Engine::Run()
    {
        // Initialize all systems
        for (auto& system : m_systems)
            system->Init();

        Timer timer;
        while (true)
        {
            Loop(ts);
        }
    }
} // namespace ap
