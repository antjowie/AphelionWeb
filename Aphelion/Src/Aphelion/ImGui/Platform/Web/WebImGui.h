#include "ImGuiSystem.h"

namespace ap
{
class APHELION_API WebImGui : public ImGuiSystem
{
public:
    WebImGui(Window* window);
    virtual ~WebImGui();

    virtual void BeginFrame() override final;
    virtual void EndFrame() override final;

private:
    Window* window;
};

} // namespace ap
