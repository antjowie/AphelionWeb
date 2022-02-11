#pragma once
#include "Aphelion/Core/Core.h"
#include "Aphelion/Core/Event/Event.h"
#include "Aphelion/Core/System.h"
#include "Aphelion/ImGui/ImGuiSystem.h"
#include "Aphelion/Window/Window.h"

#include <memory>
#include <vector>

namespace ap
{

/**
 * Engine is the runtime of the application. Call Run once you have added all your systems
 */
class Engine
{
public:
    APHELION_API static void Run();

    APHELION_API static void AddSystem(std::unique_ptr<System>&& system);
    APHELION_API static void AddSystems(std::vector<std::unique_ptr<System>>&& systems);

private:
    Engine();
    ~Engine() = default;

    static Engine& Get();

    void InitSystems();
    void RequestShutdown();
    void Loop(float ts);
    void PushEvent(Event&& event);

    std::vector<std::unique_ptr<System>> systems;
    std::unique_ptr<Window> window;
    std::unique_ptr<ImGuiSystem> imgui;

    bool shutdownRequested = false;
};
} // namespace ap
