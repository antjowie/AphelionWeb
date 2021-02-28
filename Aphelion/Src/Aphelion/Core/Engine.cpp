#include "Aphelion/Core/Engine.hpp"
#include "Aphelion/Core/Time.hpp"
#include "Aphelion/Core/Log.hpp"

#include <memory>

namespace ap
{
    Engine& Engine::Get()
    {
        static Engine engine;
        return engine;
    }
    
    Engine::Engine()
    {
        Log::Init();
    }

    void Engine::Loop(float ts)
    {
        for (auto& system : m_systems)
            system->Update(ts);
        for (auto& system : m_systems)
            system->Draw();
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