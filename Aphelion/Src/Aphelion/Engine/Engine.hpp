#pragma once
#include <memory>
#include <vector>

#include "Aphelion/Core/Core.hpp"
#include "Aphelion/Core/Event/Event.hpp"
#include "Aphelion/Core/System.hpp"
#include "Aphelion/ImGUI/ImGUISystem.hpp"
#include "Aphelion/Window/Window.hpp"

namespace ap
{

/**
 * Engine is the runtime of the application. To use this either check the Sanbox
 * project.
 *
 * Usage example
 * 1. Create instance of the engine
 *  Engine instance;
 * 2. Add your own systems
 *  instance.AddSystem(ExampleSystem());
 * 3. Run the engine
 *  instance.Run();
 */
class APHELION_API Engine
{
public:
    static Engine& Get();

    void Run();

    void AddSystem(std::unique_ptr<System>&& system);
    void AddSystems(std::vector<std::unique_ptr<System>>&& systems);

private:
    Engine();

    void Init();
    void Loop(float ts);
    void PushEvent(Event&& event);

    std::vector<std::unique_ptr<System>> m_systems;
    std::unique_ptr<Window> m_window;
    std::unique_ptr<ImGUISystem> m_imgui;
};
} // namespace ap
