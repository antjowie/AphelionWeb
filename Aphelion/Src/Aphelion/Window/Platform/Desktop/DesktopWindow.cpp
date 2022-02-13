#include "Platform/Desktop/DesktopWindow.h"
#include "Aphelion/Core/Log.h"
#include "Aphelion/Core/Event/KeyEvent.h"
#include "Aphelion/Core/Event/MouseEvent.h"
#include "Aphelion/Core/Event/WindowEvent.h"

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
    glfwSetErrorCallback([](int error, const char* description) {
        AP_CORE_ERROR("Window(glfw) error event({}): {}", error, description);
    });

    // Create GLFW window
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    window = glfwCreateWindow(props.width, props.height, props.title.c_str(), nullptr, nullptr);
    AP_CORE_ASSERT(window, "Failed to create glfw window or OpenGL context");

    glfwSetWindowUserPointer(window, &this->props);

    // Setup glad and OpenGL contxt
    glfwMakeContextCurrent(window);
    AP_CORE_VERIFY(gladLoadGL(glfwGetProcAddress), "Failed to initialize OpenGL context")
    AP_CORE_INFO("OpenGL Info:");
    AP_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
    AP_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
    AP_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));

    // Setup window events
    glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height) {
        WindowProps& props = *(WindowProps*)glfwGetWindowUserPointer(window);
        props.width = width;
        props.height = height;

        props.eventCb(WindowResizeEvent(width, height));
    });
    glfwSetWindowCloseCallback(window, [](GLFWwindow* window) {
        WindowProps& props = *(WindowProps*)glfwGetWindowUserPointer(window);

        props.eventCb(WindowCloseEvent());
    });

    glfwSetWindowPosCallback(window, [](GLFWwindow* window, int xpos, int ypos) {
        WindowProps& props = *(WindowProps*)glfwGetWindowUserPointer(window);

        props.eventCb(WindowMoveEvent(xpos, ypos));
    });

    glfwSetWindowIconifyCallback(window, [](GLFWwindow* window, int iconify) {
        WindowProps& props = *(WindowProps*)glfwGetWindowUserPointer(window);

        props.eventCb(WindowIconifyEvent(iconify));
    });

    glfwSetWindowFocusCallback(window, [](GLFWwindow* window, int focused) {
        WindowProps& props = *(WindowProps*)glfwGetWindowUserPointer(window);

        props.eventCb(WindowFocusEvent(focused));
    });

    // Setup key events
    // The scancode is unique for every key, regardless of whether it has a key token. Scancodes are platform-specific
    // but consistent over time, so keys will have different scancodes depending on the platform but they are safe to
    // save to disk. You can query the scancode for any named key on the current platform with glfwGetKeyScancode.
    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        WindowProps& props = *static_cast<WindowProps*>(glfwGetWindowUserPointer(window));

        switch (action)
        {
        case GLFW_PRESS:
            props.eventCb(KeyPressedEvent(key, 0));
            break;
        case GLFW_REPEAT:
            props.eventCb(KeyPressedEvent(key, 1));
            break;
        case GLFW_RELEASE:
            props.eventCb(KeyReleasedEvent(key));
            break;

        default:
            AP_CORE_WARN("Unhandled input action {}", action);
            break;
        }
        glfwSetCharCallback(window, [](GLFWwindow* window, unsigned int keycode) {
            WindowProps& props = *(WindowProps*)glfwGetWindowUserPointer(window);

            props.eventCb(KeyTypedEvent(keycode));
        });
    });

    // Setup mouse events
    glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
        WindowProps& props = *(WindowProps*)glfwGetWindowUserPointer(window);

        switch (action)
        {
        case GLFW_PRESS: {
            props.eventCb(MouseButtonPressedEvent(button));
            break;
        }
        case GLFW_RELEASE: {
            props.eventCb(MouseButtonReleasedEvent(button));
            break;
        }
        }
    });
    glfwSetScrollCallback(window, [](GLFWwindow* window, double xOffset, double yOffset) {
        WindowProps& props = *(WindowProps*)glfwGetWindowUserPointer(window);
        props.eventCb(MouseScrolledEvent((float)xOffset, (float)yOffset));
    });
    glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xPos, double yPos) {
        WindowProps& props = *(WindowProps*)glfwGetWindowUserPointer(window);
        props.eventCb(MouseMovedEvent((float)xPos, (float)yPos));
    });

    AP_CORE_INFO("Created glfw window");
}

DesktopWindow::~DesktopWindow()
{
    if (window)
    {
        AP_CORE_TRACE("Destroying window");
        glfwDestroyWindow(window);
    }
    AP_CORE_TRACE("Terminating glfw");
    glfwTerminate();
}

void DesktopWindow::Update()
{
    glfwPollEvents();
    glfwSwapBuffers(window);

    glClear(GL_COLOR_BUFFER_BIT);
}

std::pair<unsigned, unsigned> DesktopWindow::GetSize() const
{
    return {props.width, props.height};
}

void DesktopWindow::SetVSync(bool enable)
{
    glfwSwapInterval(enable ? 1 : 0);
}

} // namespace ap
