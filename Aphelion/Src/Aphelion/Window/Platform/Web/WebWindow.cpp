#include "Platform/Web/WebWindow.hpp"

#include <SDL2/sdl.h>

#include "Aphelion/Core/Log.hpp"
// #include <GLES2/gl3.h>
#include <GLES2/gl2.h>

namespace ap {
std::unique_ptr<Window> Window::Create(WindowProps props) {
  // return nullptr;
  return std::make_unique<WebWindow>(props);
}

WebWindow::WebWindow(WindowProps props) {
  // Setup SDL
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    AP_CORE_CRITICAL("Window creation SDL Init failed! {}", SDL_GetError());
    throw -1;
  }

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

  // Create window with graphics context
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
  SDL_DisplayMode current;
  SDL_GetCurrentDisplayMode(0, &current);
  SDL_WindowFlags window_flags = (SDL_WindowFlags)(
      SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
  m_window = SDL_CreateWindow(props.title.c_str(), SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, props.width, props.height,
                              window_flags);
  static auto context = SDL_GL_CreateContext(m_window);
  if (!context) {
    AP_CORE_CRITICAL("Window creation SDL Context failed! {}", SDL_GetError());
    throw 1;
  }
  SDL_GL_SetSwapInterval(1);  // Enable vsync
  AP_CORE_TRACE("Created Window");
  AP_CORE_INFO("OpenGL Specs:");
  AP_CORE_INFO("  Vendor: {}", glGetString(GL_VENDOR));
  AP_CORE_INFO("  Renderer: {}", glGetString(GL_RENDERER));
  AP_CORE_INFO("  Version: {}", glGetString(GL_VERSION));
}

unsigned WebWindow::GetWidth() const {
  int width;
  int height;
  SDL_GetWindowSize(m_window, &width, &height);
  return width;
}

unsigned WebWindow::GetHeight() const {
  int width;
  int height;
  SDL_GetWindowSize(m_window, &width, &height);
  return height;
}

void WebWindow::Update() {
  // Poll the events
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    AP_CORE_TRACE("Event {}", event.type);
    // TODO: Handle them event :)
  }

  SDL_GL_SwapWindow(m_window);
}

// void WebWindow::SetEventCallback(const EventCallbackFn& callback)
// {

// }

void WebWindow::SetVSync(bool enable) {
  SDL_GL_SetSwapInterval(enable ? 1 : 0);  // Enable vsync
}

void *WebWindow::GetNativeWindow() { return m_window; }

}  // namespace ap