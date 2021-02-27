#include "Aphelion/Core/Engine.hpp"
#include "Aphelion/Core/Time.hpp"

#include <emscripten.h>

// https://emscripten.org/docs/porting/emscripten-runtime-environment.html#browser-main-loop
// We can't have an infinite loop for web browsers since the js code expects to return
namespace ap
{       
    void Engine::Run()
    {
        // Initialize all systems
        for (auto& system : m_systems)
            system->Init();

        // auto frameFunc = [this]()
        // {
        //     Timer timer;
        //     float ts = timer.Reset();

        //     for (auto& system : m_systems)
        //         system->Update(ts);
        //     for (auto& system : m_systems)
        //         system->Draw();
        // };

        emscripten_set_main_loop_arg([](void* engine)
        {
            static Timer time;
            reinterpret_cast<Engine*>(engine)->Loop(time.Reset());
        },
        this, 0, true);
    }
} // namespace ap
