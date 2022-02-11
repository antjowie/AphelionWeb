#include "Aphelion/Engine/Engine.h"
#include "Aphelion/Core/Event/WindowEvent.h"

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
    AP_CORE_TRACE("Constructing engine");

    // Create window
    WindowProps props;
    props.eventCb = [&](Event&& e) { PushEvent(std::move(e)); };
    window = Window::Create(props);

    // Add window close event handler
    class AppCloseSystem : public System
    {
        virtual void OnEvent(Event& event) override final
        {
            if (event.GetEventType() == EventType::WindowClose)
            {
                Engine::Get().RequestShutdown();
            }
        }
    };
    systems.push_back(std::make_unique<AppCloseSystem>());

    // Create ImGUI
    imgui = ImGuiSystem::Create(window.get());
}

void Engine::InitSystems()
{
    AP_CORE_TRACE("Intializing systems");
    for (auto& system : systems)
        system->Init();
}

void Engine::RequestShutdown()
{
    shutdownRequested = true;
}

void Engine::Loop(float ts)
{
    for (auto& system : systems)
        system->OnUpdate(ts);

    window->Update();

    imgui->BeginFrame();
    for (auto& system : systems)
        system->OnDraw();
    imgui->EndFrame();
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
    Get().systems.push_back(std::move(system));
}

void Engine::AddSystems(std::vector<std::unique_ptr<System>>&& systems)
{
    for (auto& system : systems)
        AddSystem(std::move(system));
}
} // namespace ap
