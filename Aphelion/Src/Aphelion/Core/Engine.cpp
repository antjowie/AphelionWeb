#include "Engine.hpp"
#include "Time.hpp"

#include <memory>

namespace ap
{
    Engine::Engine()
    {
        Log::Init();
    }
    
    void Engine::Run()
    {
        // Initialize all systems
        for (auto& system : m_systems)
            system->Init();

        Timer timer;
        while (true)
        {
            float ts = timer.Reset();

            for (auto& system : m_systems)
                system->Update(ts);
            for (auto& system : m_systems)
                system->Draw();
        }
    }

    void Engine::AddSystem(std::unique_ptr<System>&& system)
    {
        m_systems.push_back(std::move(system));
    }

    void Engine::AddSystems(std::vector<std::unique_ptr<System>>&& systems)
    {
        for (auto& system : systems)
            AddSystem(std::move(system));
    }
}