#include "Aphelion/Window/Window.hpp"
#include "ImGUI.hpp"

namespace ap {
class APHELION_API WebImGUI : public ImGUI {
 public:
  WebImGUI(const std::unique_ptr<Window>& window);
  virtual ~WebImGUI() override final;

  virtual void BeginFrame() override final;
  virtual void EndFrame() override final;

 private:
  const std::unique_ptr<Window>& m_window;
};

}  // namespace ap
