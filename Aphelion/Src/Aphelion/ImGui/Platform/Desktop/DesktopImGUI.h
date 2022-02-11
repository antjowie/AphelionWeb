#include "Aphelion/ImGui/ImGUISystem.h"

namespace ap
{
class Window;

class DesktopImGui : public ImGuiSystem
{
public:
    DesktopImGui(Window* window);
    virtual ~DesktopImGui();

    virtual void OnEvent(Event& event) override final;
    virtual void BeginFrame() override final;
    virtual void EndFrame() override final;

private:
    Window* window;
};

} // namespace ap
