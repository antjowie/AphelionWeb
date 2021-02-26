#pragma once

namespace ap
{
    /**
     * The engine runs systems. 
     * At the moment systems runs synchroniously, but 
     * in the future they will run concurrent. I have 
     * yet to design how that will happen. 
     */
    class APHELION_API System
    {
    public:
        virtual void Init() {};
        virtual void Update(float ts) {};
        virtual void Draw() {};
    };
}