#include "Aphelion/Core/Core.hpp"
#include "Aphelion/Core/Log.hpp"
#include <emscripten/emscripten.h>
#include "Aphelion/Core/Engine.hpp"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

class TestSystem : public ap::System
{
public:
    virtual void Init() override final {
        //AP_TRACE("Hello WASM! {:2f}", ts);

    }

    virtual void Update(float ts) override final {
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