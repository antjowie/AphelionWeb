#include "Aphelion/Core/Engine.hpp"
#include "Aphelion/Core/Time.hpp"

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
