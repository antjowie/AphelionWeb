#pragma once
#include "System.hpp"

namespace ap
{
    //class System;

    /**
     * Engine is the runtime of the application. The user creates 
     * an instance of this class and passes whatever systems they 
     * require from it
     */
    class APHELION_API Engine
    {
    public: 
        Engine();

        void Run();
        void AddSystem(std::unique_ptr<System>&& system);
        void AddSystems(std::vector<std::unique_ptr<System>>&& systems);

    private:
        std::vector<std::unique_ptr<System>> m_systems;
    };
}