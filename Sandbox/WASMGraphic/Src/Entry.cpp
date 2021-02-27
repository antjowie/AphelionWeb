#include "Aphelion/Core/Core.hpp"
#include "Aphelion/Core/Log.hpp"
#include "Aphelion/Core/Engine.hpp"

class TestSystem : public ap::System
{
public:
    virtual void Init() override final {
        //AP_TRACE("Hello WASM! {:2f}", ts);

    }

    virtual void Update(float ts) override final {
        AP_TRACE("Hello there fps:{}", 1.f/ts);
        
    }

    virtual void Draw() override final {



    }
};

int main() {
    ap::Engine engine;
    AP_TRACE("Hello WASM!");
    engine.AddSystem(std::make_unique<TestSystem>());
    engine.Run();
}