#include "Aphelion/Renderer/RenderCommand.h"

namespace ap
{
std::unique_ptr<RendererAPI> RenderCommand::rendererAPI = RendererAPI::Create();
}
