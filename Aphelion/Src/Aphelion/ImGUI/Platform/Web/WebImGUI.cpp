#include "Platform/Web/WebImGUI.hpp"

#include <GLES3/gl3.h>
#include <SDL2/SDL.h>
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_sdl.h>

#include "Aphelion/Core/Event/Event.hpp"
#include "Aphelion/Window/Window.hpp"

// https://github.com/ocornut/imgui/blob/master/examples/example_emscripten_opengl3/main.cpp
namespace ap
{
bool OnNativeEvent(void* event)
{
    ImGui_ImplSDL2_ProcessEvent(reinterpret_cast<SDL_Event*>(event));
    ImGuiIO& io = ImGui::GetIO();
    return io.WantCaptureMouse || io.WantCaptureKeyboard;
}

std::unique_ptr<ImGUISystem> ImGUISystem::Create(Window* window)
{
    return std::make_unique<WebImGUI>(window);
}

inline SDL_Window* ToSDLWindow(Window* window)
{
    return reinterpret_cast<SDL_Window*>(window->GetNativeWindow());
}

WebImGUI::WebImGUI(Window* window)
    : m_window(window)
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable
    // Keyboard Controls io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; //
    // Enable Gamepad Controls

    // For an Emscripten build we are disabling file-system access, so let's not
    // attempt to do a fopen() of the imgui.ini file. You may manually call
    // LoadIniSettingsFromMemory() to load settings from your own storage.
    io.IniFilename = NULL;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    // ImGui::StyleColorsClassic();

    // Setup Platform/Renderer backends
    const char* glsl_version = "#version 300 es";
    SDL_GLContext context = SDL_GL_GetCurrentContext();
    ImGui_ImplSDL2_InitForOpenGL(ToSDLWindow(m_window), &context);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can
    // also load multiple fonts and use ImGui::PushFont()/PopFont() to select
    // them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you
    // need to select the font among multiple.
    // - If the file cannot be loaded, the function will return NULL. Please
    // handle those errors in your application (e.g. use an assertion, or display
    // an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored
    // into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which
    // ImGui_ImplXXXX_NewFrame below will call.
    // - Read 'docs/FONTS.md' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string
    // literal you need to write a double backslash \\ !
    // - Emscripten allows preloading a file or folder to be accessible at
    // runtime. See Makefile for details.
    // io.Fonts->AddFontDefault();

    // Setup event middleware
    window->SetEventMiddleware(OnNativeEvent);
}

WebImGUI::~WebImGUI()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}

void WebImGUI::BeginFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(ToSDLWindow(m_window));
    ImGui::NewFrame();
}

void WebImGUI::EndFrame()
{
    ImGui::Render();
    SDL_GL_MakeCurrent(ToSDLWindow(m_window), SDL_GL_GetCurrentContext());
    glViewport(0, 0, m_window->GetWidth(), m_window->GetHeight());
    // glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w,
    //              clear_color.z * clear_color.w, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    SDL_GL_SwapWindow(ToSDLWindow(m_window));
}

} // namespace ap
