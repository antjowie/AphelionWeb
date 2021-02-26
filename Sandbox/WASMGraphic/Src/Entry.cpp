#include "Aphelion/Core/Engine.hpp"

class TestSystem : public ap::System
{
public:
    virtual void Update(float ts) {
        AP_TRACE("Hello WASM! {:2f}", ts);
    }
};

int main() {
    ap::Engine engine;
    AP_TRACE("Hello WASM!");
    engine.AddSystem(std::make_unique<TestSystem>());
    engine.Run();
}