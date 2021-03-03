#include <memory>

#include "Aphelion/Core/Core.hpp"

namespace ap {
class Window;
/**
 * Interface for the class that handles our ImGUI state
 * The engine creates an instance of this class
 */
class APHELION_API ImGUI {
 public:
  static std::unique_ptr<ImGUI> Create(Window* window);

  // ImGUI(const std::unique_ptr<Window>& window) = default;
  virtual ~ImGUI() = default;

  virtual void BeginFrame() = 0;
  virtual void EndFrame() = 0;
};

}  // namespace ap
