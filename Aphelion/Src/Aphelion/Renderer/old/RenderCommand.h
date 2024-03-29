#pragma once

#include "Aphelion/Core/Core.h"
#include "Aphelion/Renderer/RendererAPI.h"

/**
 * Rendercommands are commands that we can query
 * By doing that, we know the whole draw state before
 * we are going to render it. This allows us to do
 * a bunch of optimizations such as batching materials
 *
 * TODO: Commands are just forwarded to the api.
 * We should buffer them and optimize based on that
 */
namespace ap
{
class APHELION_API RenderCommand
{
  public:
    static void Init()
    {
        rendererAPI->Init();
    }

    static void SetViewport(unsigned x, unsigned y, unsigned width, unsigned height)
    {
        rendererAPI->SetViewport(x, y, width, height);
    }

    static void SetClearColor(float r, float g, float b, float a)
    {
        rendererAPI->SetClearColor(r, g, b, a);
    }

    static void Clear()
    {
        rendererAPI->Clear();
    }

    static void DrawIndexed(const std::shared_ptr<VertexArray> &vertexArray, unsigned count = 0)
    {
        rendererAPI->DrawIndexed(vertexArray, count);
    }

  private:
    static std::unique_ptr<RendererAPI> rendererAPI;
};
} // namespace ap
