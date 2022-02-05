#include "Aphelion/Core/Core.h"
#include "Aphelion/Core/Log.h"
#include "Aphelion/Core/System.h"
#include "Aphelion/Engine/Engine.h"
//#include "Aphelion/Window/Window.h"
//#include "imgui.h"

class RenderSystem : public ap::System
{
  public:
    virtual void Init() override final
    {
    }

    virtual void OnUpdate(float ts) override final
    {
        AP_TRACE("Hello {}", ts);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    virtual void OnDraw() override final
    {
        // 1. Show the big demo window (Most of the sample code is in
        // ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear
        // ImGui!).
        // static bool show_demo_window = true;
        // if (show_demo_window) ImGui::ShowDemoWindow(&show_demo_window);
    }

    virtual void OnEvent(ap::Event &event) override final
    {
        AP_TRACE("Got event {}", event);
    }
};

#include <iostream>
int main()
{
    ap::Engine::Get().AddSystem(std::make_unique<RenderSystem>());
    ap::Engine::Get().Run();
}
