#pragma once
#include <memory>
#include <vector>

#include "Aphelion/Core/Core.hpp"
#include "Aphelion/Core/System.hpp"
#include "Aphelion/ImGUI/ImGUI.hpp"
#include "Aphelion/Window/Window.hpp"

namespace ap {

/**
 * Engine is the runtime of the application. The user creates
 * an instance of this class and passes whatever systems they
 * require from it
 */
class APHELION_API Engine {
 public:
  static Engine& Get();

  void Run();
  void Loop(float ts);

  void AddSystem(std::unique_ptr<System>&& system);
  void AddSystems(std::vector<std::unique_ptr<System>>&& systems);

 private:
  Engine();

  std::vector<std::unique_ptr<System>> m_systems;
  std::unique_ptr<Window> m_window;
  std::unique_ptr<ImGUI> m_imgui;
};
}  // namespace ap