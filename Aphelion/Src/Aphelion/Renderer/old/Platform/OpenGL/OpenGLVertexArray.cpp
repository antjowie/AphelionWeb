#include "Platform/OpenGL/OpenGLVertexArray.h"

#include <glad/glad.h>

namespace ap
{
GLenum BaseTypeToOpenGLType(ShaderDataType type)
{
    switch (type)
    {
    case ShaderDataType::Float:
        return GL_FLOAT;
    case ShaderDataType::Float2:
        return GL_FLOAT;
    case ShaderDataType::Float3:
        return GL_FLOAT;
    case ShaderDataType::Float4:
        return GL_FLOAT;
    case ShaderDataType::Mat3:
        return GL_FLOAT;
    case ShaderDataType::Mat4:
        return GL_FLOAT;
    case ShaderDataType::Int:
        return GL_INT;
    case ShaderDataType::Int2:
        return GL_INT;
    case ShaderDataType::Int3:
        return GL_INT;
    case ShaderDataType::Int4:
        return GL_INT;
    case ShaderDataType::Bool:
        return GL_BOOL;
    }
}

OpenGLVertexArray::OpenGLVertexArray()
{
    glCreateVertexArrays(1, &m_id);
}

OpenGLVertexArray::~OpenGLVertexArray()
{
    glDeleteVertexArrays(1, &m_id);
}

void OpenGLVertexArray::Bind()
{
    glBindVertexArray(m_id);
}

void OpenGLVertexArray::Unbind()
{
    glBindVertexArray(0);
}

void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer> &buffer)
{
    Bind();
    buffer->Bind();

    // Calculate stride
    unsigned stride = 0;
    for (auto elem : buffer->GetElements())
        stride += elem.size;

    unsigned index = 0;
    unsigned offset = 0;
    for (auto elem : buffer->GetElements())
    {
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index, elem.GetComponentCount(), BaseTypeToOpenGLType(elem.type),
                              elem.normalized ? GL_TRUE : GL_FALSE, stride, (void *)offset);

        index++;
        offset += elem.size;
    }

    m_buffers.push_back(buffer);
}

void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer> &buffer)
{
    Bind();
    buffer->Bind();

    m_indexBuffer = buffer;
}

VertexBufferRef OpenGLVertexArray::GetVertexBuffer(unsigned index)
{
    return m_buffers[index];
}

const VertexBufferRef &OpenGLVertexArray::GetVertexBuffer(unsigned index) const
{
    return m_buffers[index];
}

const std::shared_ptr<IndexBuffer> &OpenGLVertexArray::GetIndexBuffer() const
{
    return m_indexBuffer;
}
} // namespace ap
