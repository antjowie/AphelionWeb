#include "ImGUI.hpp"

namespace ap {
class APHELION_API WebImGUI : public ImGUI {
 public:
  WebImGUI(Window* window);
  virtual ~WebImGUI();

  virtual void BeginFrame() override final;
  virtual void EndFrame() override final;

 private:
  Window* m_window;
};

}  // namespace ap
