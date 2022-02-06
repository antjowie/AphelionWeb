#include "Platform/Web/WebWindow.h"

#include "Aphelion/Core/Event/KeyEvent.h"
#include "Aphelion/Core/Event/MouseEvent.h"
#include "Aphelion/Core/Event/WindowEvent.h"
#include "Aphelion/Core/Log.h"

#include <GLES3/gl3.h>
#include <SDL2/sdl.h>

namespace ap
{
std::unique_ptr<Window> Window::Create(WindowProps props)
{
    // return nullptr;
    return std::make_unique<WebWindow>(props);
}

WebWindow::WebWindow(WindowProps props) : props(props)
{
    // Setup SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
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
    SDL_WindowFlags window_flags =
        (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    window = SDL_CreateWindow(props.title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, props.width,
                              props.height, window_flags);
    static auto context = SDL_GL_CreateContext(window);
    if (!context)
    {
        AP_CORE_CRITICAL("Window creation SDL Context failed! {}", SDL_GetError());
        throw 1;
    }
    SDL_GL_SetSwapInterval(1); // Enable vsync
    AP_CORE_TRACE("Created Window");
    AP_CORE_INFO("OpenGL Specs:");
    AP_CORE_INFO("  Vendor: {}", glGetString(GL_VENDOR));
    AP_CORE_INFO("  Renderer: {}", glGetString(GL_RENDERER));
    AP_CORE_INFO("  Version: {}", glGetString(GL_VERSION));
}

unsigned WebWindow::GetWidth() const
{
    int width;
    int height;
    SDL_GetWindowSize(window, &width, &height);
    return width;
}

unsigned WebWindow::GetHeight() const
{
    int width;
    int height;
    SDL_GetWindowSize(window, &width, &height);
    return height;
}

void WebWindow::SetEventMiddleware(EventMiddlewareFn fn)
{
    eventMiddleware = fn;
}

void WebWindow::Update()
{
    // Poll the events
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        // If we have a middleware, have it handle it first
        if (eventMiddleware && eventMiddleware(&event))
            continue;

        // Convert SDL event to Aphelion event and propogate to systems
        switch (event.type)
        {
        case SDL_QUIT: /**< User-requested quit */
            props.eventCallback(WindowCloseEvent());
            break;

        /* These application events have special meaning on iOS, see README-ios.md
         * for details */
        case SDL_APP_TERMINATING:
            AP_CORE_WARN("SDL_APP_TERMINATING not handled in window");
            break; /**< The application is being terminated by the OS
                                  Called on iOS in applicationWillTerminate()
                                  Called on Android in onDestroy()
                             */
        case SDL_APP_LOWMEMORY:
            AP_CORE_WARN("SDL_APP_LOWMEMORY not handled in window");

            break; /**< The application is low on memory, free memory if possible.
                                Called on iOS in
                  applicationDidReceiveMemoryWarning() Called on Android in
                  onLowMemory()
                           */
        case SDL_APP_WILLENTERBACKGROUND:
            AP_CORE_WARN("SDL_APP_WILLENTERBACKGROUND not handled in window");

            break; /**< The application is about to enter the background
                                         Called on iOS in
                  applicationWillResignActive() Called on Android in onPause()
                                    */
        case SDL_APP_DIDENTERBACKGROUND:
            AP_CORE_WARN("SDL_APP_DIDENTERBACKGROUND not handled in window");
            break; /**< The application did enter the background and may not get CPU
                  for some time Called on iOS in applicationDidEnterBackground()
                                         Called on Android in onPause()
                                    */
        case SDL_APP_WILLENTERFOREGROUND:
            AP_CORE_WARN("SDL_APP_WILLENTERFOREGROUND not handled in window");
            break; /**< The application is about to enter the foreground
                                         Called on iOS in
                  applicationWillEnterForeground() Called on Android in
                  onResume()
                                    */
        case SDL_APP_DIDENTERFOREGROUND:
            AP_CORE_WARN("SDL_APP_DIDENTERFOREGROUND not handled in window");
            break; /**< The application is now interactive
                                         Called on iOS in
                  applicationDidBecomeActive() Called on Android in onResume()
                                    */

        /* Display events */
        case SDL_DISPLAYEVENT:
            AP_CORE_WARN("SDL_DISPLAYEVENT not handled in window");
            break; /**< Display state change */

        /* Window events */
        case SDL_WINDOWEVENT: {
            auto& window = event.window;
            switch (window.event)
            {
            case SDL_WINDOWEVENT_SHOWN:
                props.eventCallback(WindowIconifyEvent(false));
                break;
            case SDL_WINDOWEVENT_HIDDEN:
                props.eventCallback(WindowIconifyEvent(true));
                break;
            case SDL_WINDOWEVENT_EXPOSED:
                AP_CORE_WARN("SDL_WINDOWEVENT_EXPOSED not handled in window");
                break;
            case SDL_WINDOWEVENT_MOVED:
                props.eventCallback(WindowMoveEvent(window.data1, window.data2));
                break;
            case SDL_WINDOWEVENT_RESIZED:
                props.eventCallback(WindowResizeEvent(window.data1, window.data2));
                break;
            case SDL_WINDOWEVENT_SIZE_CHANGED:
                props.eventCallback(WindowResizeEvent(window.data1, window.data2));
                break;
            case SDL_WINDOWEVENT_MINIMIZED:
                AP_CORE_WARN("SDL_WINDOWEVENT_MINIMIZED not handled in window");
                break;
            case SDL_WINDOWEVENT_MAXIMIZED:
                AP_CORE_WARN("SDL_WINDOWEVENT_MAXIMIZED not handled in window");
                break;
            case SDL_WINDOWEVENT_RESTORED:
                AP_CORE_WARN("SDL_WINDOWEVENT_RESTORED not handled in window");
                break;
            case SDL_WINDOWEVENT_ENTER:
                AP_CORE_WARN("SDL_WINDOWEVENT_ENTER not handled in window");
                break;
            case SDL_WINDOWEVENT_LEAVE:
                AP_CORE_WARN("SDL_WINDOWEVENT_LEAVE not handled in window");
                break;
            case SDL_WINDOWEVENT_FOCUS_GAINED:
                AP_CORE_WARN("SDL_WINDOWEVENT_FOCUS_GAINED not handled in window");
                break;
            case SDL_WINDOWEVENT_FOCUS_LOST:
                AP_CORE_WARN("SDL_WINDOWEVENT_FOCUS_LOST not handled in window");
                break;
            case SDL_WINDOWEVENT_CLOSE:
                props.eventCallback(WindowCloseEvent());
                break;
            case SDL_WINDOWEVENT_TAKE_FOCUS:
                AP_CORE_WARN("SDL_WINDOWEVENT_TAKE_FOCUS not handled in window");
                break;
            case SDL_WINDOWEVENT_HIT_TEST:
                AP_CORE_WARN("SDL_WINDOWEVENT_HIT_TEST not handled in window");
                break;
            default:
                AP_CORE_WARN("SDL_WINDOWEVENT_*** not handled id({})", event.window.event);
            }
        }
        break; /**< Window state change */
        case SDL_SYSWMEVENT:
            AP_CORE_WARN("SDL_SYSWMEVENT not handled in window");
            break; /**< System specific event */

        // TODO: Move bottom events to WebInput

        /* Keyboard events */
        case SDL_KEYDOWN:
            props.eventCallback(KeyPressedEvent(event.key.keysym.sym, event.key.repeat)); /**< Key pressed */
        case SDL_KEYUP:
            props.eventCallback(KeyReleasedEvent(event.key.keysym.sym)); /**< Key pressed */
        case SDL_TEXTEDITING:
            props.eventCallback(KeyTypedEvent(event.key.keysym.sym));
            break; /**< Keyboard text editing (composition) */
        case SDL_TEXTINPUT:
            AP_CORE_WARN("SDL_TEXTINPUT not handled in window");
            break; /**< Keyboard text input */
        case SDL_KEYMAPCHANGED:
            AP_CORE_WARN("SDL_KEYMAPCHANGED not handled in window");
            break; /**< Keymap changed due to a system event such as an
                                input language or keyboard layout change.
                           */

        /* Mouse events */
        case SDL_MOUSEMOTION:
            props.eventCallback(MouseMovedEvent(event.motion.x, event.motion.y));

            break; /**< Mouse moved */
        case SDL_MOUSEBUTTONDOWN:
            props.eventCallback(MouseButtonPressedEvent(event.button.button));
            break; /**< Mouse button pressed */
        case SDL_MOUSEBUTTONUP:
            props.eventCallback(MouseButtonReleasedEvent(event.button.button));
            break; /**< Mouse button released */
        case SDL_MOUSEWHEEL:
            props.eventCallback(MouseScrolledEvent(event.wheel.x, event.wheel.y));
            break; /**< Mouse wheel motion */

        /* Joystick events */
        case SDL_JOYAXISMOTION:
            // break; /**< Joystick axis motion */
        case SDL_JOYBALLMOTION:
            // break; /**< Joystick trackball motion */
        case SDL_JOYHATMOTION:
            // break; /**< Joystick hat position change */
        case SDL_JOYBUTTONDOWN:
            // break; /**< Joystick button pressed */
        case SDL_JOYBUTTONUP:
            // break; /**< Joystick button released */
        case SDL_JOYDEVICEADDED:
            // break; /**< A new joystick has been inserted into the system */
        case SDL_JOYDEVICEREMOVED:
            // break; /**< An opened joystick has been removed */
            AP_CORE_WARN("SDL_JOY*** events not implemented");
            break;

        /* Game controller events */
        case SDL_CONTROLLERAXISMOTION:
            // break; /**< Game controller axis motion */
        case SDL_CONTROLLERBUTTONDOWN:
            // break; /**< Game controller button pressed */
        case SDL_CONTROLLERBUTTONUP:
            // break; /**< Game controller button released */
        case SDL_CONTROLLERDEVICEADDED:
            // break; /**< A new Game controller has been inserted into the system
            // */
        case SDL_CONTROLLERDEVICEREMOVED:
            // break; /**< An opened Game controller has been removed */
        case SDL_CONTROLLERDEVICEREMAPPED:
            // break; /**< The controller mapping was updated */
            AP_CORE_WARN("SDL_JOY*** events not implemented");
            break;

        /* Touch events */
        case SDL_FINGERDOWN:
            // break;
        case SDL_FINGERUP:
            // break;
        case SDL_FINGERMOTION:
            AP_CORE_WARN("SDL_FINGERMOTION*** events not implemented");
            break;

        /* Gesture events */
        case SDL_DOLLARGESTURE:
            // break;
        case SDL_DOLLARRECORD:
            // break;
        case SDL_MULTIGESTURE:
            AP_CORE_WARN("SDL_GESTURE*** events not implemented");
            break;

        /* Clipboard events */
        case SDL_CLIPBOARDUPDATE:
            AP_CORE_WARN("SDL_CLIPBOARDUPDATE events not implemented");
            break; /**< The clipboard changed */

        /* Drag and drop events */
        case SDL_DROPFILE:
            // break; /**< The system requests a file open */
        case SDL_DROPTEXT:
            // break; /**< text/plain drag-and-drop event */
        case SDL_DROPBEGIN:
            // break; /**< A new set of drops is beginning (NULL filename) */
        case SDL_DROPCOMPLETE:
            // break; /**< Current set of drops is now complete (NULL filename) */
            AP_CORE_WARN("SDL_DROP*** events not implemented");
            break;

        /* Audio hotplug events */
        case SDL_AUDIODEVICEADDED:
            // break; /**< A new audio device is available */
        case SDL_AUDIODEVICEREMOVED:
            // break; /**< An audio device has been removed. */
            AP_CORE_WARN("SDL_AUDIO*** events not implemented");
            break;

        /* Sensor events */
        case SDL_SENSORUPDATE:
            AP_CORE_WARN("SDL_SENSORUPDATE events not implemented");
            break; /**< A sensor was updated */

        /* Render events */
        case SDL_RENDER_TARGETS_RESET:
            // break; /**< The render targets have been reset and their contents
            // need
            //           to be updated */
        case SDL_RENDER_DEVICE_RESET:
            // break; /**< The device has been reset and all textures need to be
            //           recreated */
            AP_CORE_WARN("SDL_RENDER_*** events not implemented");
            break;
        default:
            AP_CORE_WARN("Unhandled event in window id {}", event.type);
            break;
        }
    }

    SDL_GL_SwapWindow(window);
}

// void WebWindow::SetEventCallback(const EventCallbackFn& callback)
// {

// }

void WebWindow::SetVSync(bool enable)
{
    SDL_GL_SetSwapInterval(enable ? 1 : 0); // Enable vsync
}

void* WebWindow::GetNativeWindow()
{
    return window;
}

} // namespace ap
