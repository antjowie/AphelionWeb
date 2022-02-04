#include "ImGUISystem.h"

namespace ap
{
class APHELION_API WebImGUI : public ImGUISystem
{
  public:
    WebImGUI(Window *window);
    virtual ~WebImGUI();

    virtual void BeginFrame() override final;
    virtual void EndFrame() override final;

  private:
    Window *m_window;
};

} // namespace ap
