#include "Aphelion/Renderer/VertexBuffer.h"

#include "Aphelion/Renderer/RendererAPI.h"
#include "Platform/OpenGL/OpenGLVertexBuffer.h"

namespace ap
{
uint32_t BufferElement::GetComponentCount() const
{
    switch (type)
    {
    case ShaderDataType::Float:
        return 1;
    case ShaderDataType::Float2:
        return 2;
    case ShaderDataType::Float3:
        return 3;
    case ShaderDataType::Float4:
        return 4;
    case ShaderDataType::Mat3:
        return 3; // 3* float3
    case ShaderDataType::Mat4:
        return 4; // 4* float4
    case ShaderDataType::Int:
        return 1;
    case ShaderDataType::Int2:
        return 2;
    case ShaderDataType::Int3:
        return 3;
    case ShaderDataType::Int4:
        return 4;
    case ShaderDataType::Bool:
        return 1;
    }

    AP_CORE_ASSERT(false, "Unknown ShaderDataType!");
    return 0;
}

void VertexBuffer::AddElement(const BufferElement &elem)
{
    elements.push_back(elem);
}

const std::vector<BufferElement> &VertexBuffer::GetElements() const
{
    return elements;
}

std::shared_ptr<VertexBuffer> VertexBuffer::Create(uint32_t size)
{
    switch (RendererAPI::GetAPI())
    {
    case RendererAPI::API::None:
        AP_CORE_CRITICAL("Buffer NONE is not yet implemented");
    case RendererAPI::API::OpenGL:
        return std::make_shared<OpenGLVertexBuffer>(size);
    }
}

std::shared_ptr<VertexBuffer> VertexBuffer::Create(const float *vertices, uint32_t size)
{
    switch (RendererAPI::GetAPI())
    {
    case RendererAPI::API::None:
        AP_CORE_CRITICAL("Buffer NONE is not yet implemented");
    case RendererAPI::API::OpenGL:
        return std::make_shared<OpenGLVertexBuffer>(vertices, size);
    }
}

std::shared_ptr<IndexBuffer> IndexBuffer::Create(const uint32_t *indices, uint32_t count)
{
    switch (RendererAPI::GetAPI())
    {
    case RendererAPI::API::None:
        AP_CORE_CRITICAL("Index Buffer NONE is not yet implemented");
    case RendererAPI::API::OpenGL:
        return std::make_shared<OpenGLIndexBuffer>(indices, count);
    }
}
} // namespace ap
