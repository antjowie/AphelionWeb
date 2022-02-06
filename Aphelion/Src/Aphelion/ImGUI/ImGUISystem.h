#include "Aphelion/Core/Core.h"

#include <memory>

namespace ap
{
class Event;
class Window;
/**
 * Interface for the class that handles our ImGUI state
 * The engine creates an instance of this class
 */
class APHELION_API ImGUISystem
{
  public:
    static std::unique_ptr<ImGUISystem> Create(Window* window);

    // ImGUISystem(const std::unique_ptr<Window>& window) = default;
    virtual ~ImGUISystem() = default;

    virtual void BeginFrame() = 0;
    virtual void EndFrame() = 0;
};

} // namespace ap
