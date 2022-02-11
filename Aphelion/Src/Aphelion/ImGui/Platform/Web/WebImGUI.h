#include "ImGUISystem.h"

namespace ap
{
class APHELION_API WebImGUI : public ImGUISystem
{
public:
    WebImGUI(Window* window);
    virtual ~WebImGUI();

    virtual void BeginFrame() override final;
    virtual void EndFrame() override final;

private:
    Window* window;
};

} // namespace ap
