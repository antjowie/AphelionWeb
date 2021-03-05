#include "Aphelion/Engine/Engine.hpp"

#include <memory>

#include "Aphelion/Core/Log.hpp"
#include "Aphelion/Core/Time.hpp"

namespace ap {
Engine& Engine::Get() {
  static Engine engine;
  return engine;
}

Engine::Engine() {
  Log::Init();

  // Create window
  WindowProps props;
  props.eventCallback = [&](Event&& e) { PushEvent(std::move(e)); };
  m_window = Window::Create(props);

  // Create ImGUI
  m_imgui = ImGUISystem::Create(m_window.get());
}

void Engine::Init() {
  AP_CORE_INFO("Intializing systems");
  for (auto& system : m_systems) system->Init();
}

void Engine::Loop(float ts) {
  for (auto& system : m_systems) system->Update(ts);

  m_imgui->BeginFrame();
  for (auto& system : m_systems) system->Draw();
  m_imgui->EndFrame();

  m_window->Update();
}

void Engine::PushEvent(Event&& event) {
    for (auto& system : m_systems) {
  }
}

void Engine::AddSystem(std::unique_ptr<System>&& system) {
  m_systems.push_back(std::move(system));
}

void Engine::AddSystems(std::vector<std::unique_ptr<System>>&& systems) {
  for (auto& system : systems) AddSystem(std::move(system));
}
}  // namespace ap