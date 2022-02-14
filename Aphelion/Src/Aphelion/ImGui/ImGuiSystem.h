#include "Aphelion/Core/Core.h"

#include <memory>

namespace ap
{
class Event;
class Window;
/**
 * Interface for the class that handles our ImGui state
 * The engine creates an instance of this class
 */
class APHELION_API ImGuiSystem
{
public:
    static std::unique_ptr<ImGuiSystem> Create(Window* window);

    virtual ~ImGuiSystem() = default;

    virtual void OnEvent(Event& event) = 0;
    virtual void BeginFrame() = 0;
    virtual void EndFrame() = 0;
};

} // namespace ap
