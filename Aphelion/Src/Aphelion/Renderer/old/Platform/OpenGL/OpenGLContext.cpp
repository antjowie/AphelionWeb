#include "Platform/OpenGL/OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace ap
{
OpenGLContext::OpenGLContext(GLFWwindow *windowHandle) : window(windowHandle)
{
    AP_CORE_ASSERT(window, "Window handle can't be null");
}

void OpenGLContext::Init()
{
    // Init GLFW
    glfwMakeContextCurrent(window);

    // Init Glad
    gladLoadGLLoader(GLADloadproc(glfwGetProcAddress));
    glfwMakeContextCurrent(window);

    int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    AP_CORE_ASSERT(status, "Failed to initialize Glad!");

    AP_CORE_INFO("OpenGL Info:");
    AP_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
    AP_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
    AP_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
}

void OpenGLContext::SwapBuffers()
{
    glfwSwapBuffers(window);
}
} // namespace ap
