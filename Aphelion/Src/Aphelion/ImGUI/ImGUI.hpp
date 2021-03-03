#include <memory>

#include "Aphelion/Core/Core.hpp"
#include "Aphelion/Window/Window.hpp"

namespace ap {
/**
 * Interface for the class that handles our ImGUI state
 * The engine creates an instance of this class
 */
class APHELION_API ImGUI {
 public:
  static std::unique_ptr<ImGUI> Create(const std::unique_ptr<Window>& window);

  // ImGUI(const std::unique_ptr<Window>& window) = default;
  virtual ~ImGUI() = 0;

  virtual void BeginFrame() = 0;
  virtual void EndFrame() = 0;
};

}  // namespace ap
