#pragma once
#include "Window.hpp"

class SDL_Window;

namespace ap
{    
    class APHELION_API WebWindow : public Window
    {
    public:
        WebWindow(WindowProps props);
    
        virtual unsigned GetWidth() const override final;
        virtual unsigned GetHeight() const override final;

        /**
         * Polls the events
         */
        virtual void Update() override final;

        /**
         * Application owns a window. The window needs to send events to the application. To do this,
         * Applications gives the Window an event callback function. 
         */
        // virtual void SetEventCallback(const EventCallbackFn& callback) override final;

        virtual void SetVSync(bool enable) override final;
        
        
        /**
         * Return the native window
         * 
         * This is required to set up the ImGui renderer
         */
        virtual void* GetNativeWindow() override final;
        
    private:
        SDL_Window* m_window;
        
    };
}