#include "Platform/Web/WebWindow.hpp"
#include "Aphelion/Core/Log.hpp"

#include <SDL2/sdl.h>
// #include <GLES2/gl3.h>
#include <GLES2/gl2.h>

namespace ap
{
    std::unique_ptr<Window> Window::Create(WindowProps props)
    {
        // return nullptr;
        return std::make_unique<WebWindow>(props);
    }

    /*
    WebWindow::WebWindow()
    {
        EGLint attribList[] =
            {
                EGL_RED_SIZE, 5,
                EGL_GREEN_SIZE, 6,
                EGL_BLUE_SIZE, 5,
                EGL_ALPHA_SIZE, (flags & ES_WINDOW_ALPHA) ? 8 : EGL_DONT_CARE,
                EGL_DEPTH_SIZE, (flags & ES_WINDOW_DEPTH) ? 8 : EGL_DONT_CARE,
                EGL_STENCIL_SIZE, (flags & ES_WINDOW_STENCIL) ? 8 : EGL_DONT_CARE,
                EGL_SAMPLE_BUFFERS, (flags & ES_WINDOW_MULTISAMPLE) ? 1 : 0,
                EGL_NONE};

        if (esContext == NULL)
        {
            return GL_FALSE;
        }

        esContext->width = width;
        esContext->height = height;

        if (!WinCreate(esContext, title))
        {
            return GL_FALSE;
        }

        if (!CreateEGLContext(esContext->hWnd,
                              &esContext->eglDisplay,
                              &esContext->eglContext,
                              &esContext->eglSurface,
                              attribList))
        {
            return GL_FALSE;
        }

        return GL_TRUE;
    }
*/

    WebWindow::WebWindow(WindowProps props)
    {
        // Setup SDL
        if (SDL_Init(SDL_INIT_VIDEO) != 0)
        {
            AP_CORE_CRITICAL("Window creation SDL Init failed! {}", SDL_GetError());
            // printf("Error: %s\n", SDL_GetError());
            throw -1;
        }

        const char* glsl_version = "#version 100";
        // const char* glsl_version = "#version 300 es";
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

        // Create window with graphics context
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
        SDL_DisplayMode current;
        SDL_GetCurrentDisplayMode(0, &current);
        SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
        m_window = SDL_CreateWindow(props.title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, props.width, props.height, window_flags);
        auto context = SDL_GL_CreateContext(m_window);
        if (!context)
        {
            AP_CORE_CRITICAL("Window creation SDL Context failed! {}", SDL_GetError());
            throw 1;
        }
        AP_CORE_TRACE("Created Window"
            "  Vendor: {0}"
            "  Renderer: {1}"
            "  Version: {2}", 
            glGetString(GL_VENDOR), glGetString(GL_RENDERER), glGetString(GL_VERSION));
    }

    unsigned WebWindow::GetWidth() const
    {
        int width;
        int height;
        SDL_GetWindowSize(m_window,&width,&height);
        return width;
    }

    unsigned WebWindow::GetHeight() const
    {
        int width;
        int height;
        SDL_GetWindowSize(m_window,&width,&height);
        return height;
    }

    void WebWindow::Update()
    {
        // Poll the events
        
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            // TODO: Handle them event :)
        }
        
        SDL_GL_SwapWindow(m_window);
    }

    // void WebWindow::SetEventCallback(const EventCallbackFn& callback)
    // {

    // }

    void WebWindow::SetVSync(bool enable)
    {
        SDL_GL_SetSwapInterval(enable ? 1 : 0); // Enable vsync
    }

    void *WebWindow::GetNativeWindow()
    {
        return m_window;
    }

}