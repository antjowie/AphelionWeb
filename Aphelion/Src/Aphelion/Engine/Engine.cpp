#include "Aphelion/Engine/Engine.h"

#include "Aphelion/Core/Log.h"
#include "Aphelion/Core/Time.h"
#include "Aphelion/Window/Window.h"

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

    // Create window
    WindowProps props;
    window = Window::Create(props);
    // props.eventCallback = [&](Event&& e) { PushEvent(std::move(e)); };

    // Create ImGUI
    // imgui = ImGUISystem::Create(window.get());
}

void Engine::Init()
{
    AP_CORE_INFO("Intializing systems");
    for (auto& system : systems)
        system->Init();
}

void Engine::Loop(float ts)
{
    for (auto& system : systems)
        system->OnUpdate(ts);

    // imgui->BeginFrame();
    // for (auto &system : systems)
    //    system->OnDraw();
    // imgui->EndFrame();

    window->Update();
}

void Engine::PushEvent(Event&& event)
{
    int i = 0;
    for (auto iter = systems.rbegin(); iter != systems.rend(); iter++)
    {
        (*iter)->OnEvent(event);
        if (event.handled)
            return;
    }
}

void Engine::AddSystem(std::unique_ptr<System>&& system)
{
    systems.push_back(std::move(system));
}

void Engine::AddSystems(std::vector<std::unique_ptr<System>>&& systems)
{
    for (auto& system : systems)
        AddSystem(std::move(system));
}
} // namespace ap
