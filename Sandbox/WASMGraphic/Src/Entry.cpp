#include "Aphelion/Core/Core.hpp"
#include "Aphelion/Core/Log.hpp"
#include "Aphelion/Core/System.hpp"
#include "Aphelion/Engine/Engine.hpp"
#include "Aphelion/Window/Window.hpp"
#include "imgui.h"
class RenderSystem : public ap::System {
 public:
  virtual void Init() override final {}

  virtual void Draw() override final {
    // 1. Show the big demo window (Most of the sample code is in
    // ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear
    // ImGui!).
    static bool show_demo_window = true;
    if (show_demo_window) ImGui::ShowDemoWindow(&show_demo_window);
  }
};

int main() {
  ap::Engine::Get().AddSystem(std::make_unique<RenderSystem>());
  ap::Engine::Get().Run();
}