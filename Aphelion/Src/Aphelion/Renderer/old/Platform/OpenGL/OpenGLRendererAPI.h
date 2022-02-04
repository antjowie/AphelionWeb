#pragma once

#include "Aphelion/Core/Core.h"
#include "Aphelion/Renderer/RendererAPI.h"

namespace ap
{
class APHELION_API OpenGLRendererAPI : public RendererAPI
{
  public:
    virtual void Init() override final;
    virtual void SetViewport(unsigned x, unsigned y, unsigned width, unsigned height) override final;
    virtual void SetClearColor(float r, float g, float b, float a) override final;

    virtual void DrawIndexed(const std::shared_ptr<VertexArray> &vertexArray, uint32_t indexCount) override final;

    virtual void Clear() override final;
};
} // namespace ap
