#include "Aphelion/Window/Platform/Desktop/DesktopWindow.h"
#include "Aphelion/Core/Log.h"

#include <glad/gl.h>
#include <GLFW/glfw3.h>

namespace ap
{
std::unique_ptr<Window> Window::Create(const WindowProps& props)
{
    return std::make_unique<DesktopWindow>(props);
}

DesktopWindow::DesktopWindow(const WindowProps& props) : props(props)
{
    AP_CORE_TRACE("Creating window using glfw implementation");

    // Initialize GLFW and setup error cb
    AP_CORE_VERIFY(glfwInit(), "GLFW failed to initialize!");
    const auto errorCb = [](int error, const char* description) {
        AP_CORE_ERROR("Window(glfw) error event({}): {}", error, description);
    };
    glfwSetErrorCallback(errorCb);

    // Create GLFW window
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    window = glfwCreateWindow(props.width, props.height, props.title.c_str(), nullptr, nullptr);
    AP_CORE_ASSERT(window, "Failed to create glfw window or OpenGL context");

    // Setup glad and OpenGL contxt
    glfwMakeContextCurrent(window);
    AP_CORE_ASSERT(gladLoadGL(glfwGetProcAddress), "Failed to initialize OpenGL context")
    AP_CORE_INFO("OpenGL Info:");
    AP_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
    AP_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
    AP_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));

    // Setup events
}

DesktopWindow::~DesktopWindow()
{
    AP_CORE_TRACE("Destroying window");
    if (window)
    {
        glfwDestroyWindow(window);
    }
    glfwTerminate();
}

void DesktopWindow::Update()
{
    glfwPollEvents();
}

std::pair<unsigned, unsigned> DesktopWindow::GetSize() const
{
    int width, height;
    glfwGetWindowSize(window, &width, &height);

    return {width, height};
}

void DesktopWindow::SetVSync(bool enable)
{
    glfwSwapInterval(enable ? 1 : 0);
}

} // namespace ap
