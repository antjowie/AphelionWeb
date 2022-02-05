#include "Platform/OpenGL/OpenGLVertexBuffer.h"

#include <glad/glad.h>

namespace ap
{
OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size)
{
    glCreateBuffers(1, &id);
    SetData(nullptr, size);
    // glNamedBufferData(id, size, nullptr, GL_STATIC_DRAW);
    // glNamedBufferData(id, size, nullptr, GL_STATIC_DRAW);
    // glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
}

OpenGLVertexBuffer::OpenGLVertexBuffer(const float *vertices, uint32_t size)
{
    glCreateBuffers(1, &id);
    SetData(vertices, size);
    // Bind();
    // glNamedBufferData(id, size, vertices, GL_STATIC_DRAW);
    // glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
    glDeleteVertexArrays(1, &id);
}

void OpenGLVertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, id);
}

void OpenGLVertexBuffer::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void OpenGLVertexBuffer::SetData(const void *data, uint32_t size)
{
    // Bind();
    /*
  https://www.khronos.org/opengl/wiki/Buffer_Object

  Initially I was worried that the buffer type is not specified (glBufferData
  sets up internal state) According to the wiki however, while filling the
  buffer the target doesn't matter
  */
    glNamedBufferData(id, size, data, GL_STATIC_DRAW);
    dirty = true;
    size = size;
}

const std::vector<float> &OpenGLVertexBuffer::GetData() const
{
    if (dirty)
    {
        dirty = false;
        data.clear();
        // We have to use resize or else the vector size var doesn't get updated
        data.resize(size / sizeof(float));

        // Get data from GPU
        glGetNamedBufferSubData(id, 0, size, data.data());
    }

    return data;
}

///////////////////////////////////
// Vertex buffer
///////////////////////////////////
OpenGLIndexBuffer::OpenGLIndexBuffer(const uint32_t *indices, uint32_t count) : count(count)
{
    // glGenBuffers(1, &id);
    glCreateBuffers(1, &id);
    // Bind();
    size = sizeof(uint32_t) * count;
    glNamedBufferData(id, size, indices, GL_STATIC_DRAW);
    dirty = true;
}

OpenGLIndexBuffer::~OpenGLIndexBuffer()
{
    glDeleteBuffers(1, &id);
}

void OpenGLIndexBuffer::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void OpenGLIndexBuffer::Unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

const std::vector<uint32_t> &OpenGLIndexBuffer::GetData() const
{
    if (dirty)
    {
        dirty = false;
        data.clear();
        data.resize(size / sizeof(uint32_t));

        // Get data from GPU
        glGetNamedBufferSubData(id, 0, size, data.data());
    }

    return data;
}

uint32_t OpenGLIndexBuffer::GetCount() const
{
    return count;
}
} // namespace ap
