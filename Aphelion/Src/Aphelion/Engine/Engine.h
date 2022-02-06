#pragma once
#include "Aphelion/Core/Core.h"
#include "Aphelion/Core/Event/Event.h"
#include "Aphelion/Core/System.h"
#include "Aphelion/ImGUI/ImGUISystem.h"
#include "Aphelion/Window/Window.h"

#include <memory>
#include <vector>

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
class Engine
{
public:
    APHELION_API static Engine& Get();

    APHELION_API void Run();

    APHELION_API void AddSystem(std::unique_ptr<System>&& system);
    APHELION_API void AddSystems(std::vector<std::unique_ptr<System>>&& systems);

private:
    Engine();

    void Init();
    void Loop(float ts);
    void PushEvent(Event&& event);

    std::vector<std::unique_ptr<System>> systems;
    std::unique_ptr<Window> window;
    // std::unique_ptr<ImGUISystem> imgui;
};
} // namespace ap
