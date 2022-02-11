#include "Aphelion/Renderer/RendererAPI.h"

#include "Aphelion/Core/Log.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace ap
{
RendererAPI::API RendererAPI::api = RendererAPI::API::OpenGL;

std::unique_ptr<RendererAPI> RendererAPI::Create()
{
    switch (api)
    {
    case RendererAPI::API::None:
        AP_CORE_CRITICAL("RenderAPI None is not yet supported");
    default:
        return std::make_unique<OpenGLRendererAPI>();
        break;
    }
}
} // namespace ap
