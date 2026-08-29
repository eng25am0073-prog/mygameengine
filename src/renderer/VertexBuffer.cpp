#include "renderer/VertexBuffer.h"

#include <glad/gl.h>

namespace engine::renderer {

void VertexBuffer::Create(const void* data, std::size_t size)
{
    glGenBuffers(1, &m_bufferId);
    glBindBuffer(GL_ARRAY_BUFFER, m_bufferId);
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(size), data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::Destroy()
{
    if (m_bufferId != 0) {
        glDeleteBuffers(1, &m_bufferId);
        m_bufferId = 0;
    }
}

void VertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_bufferId);
}

void VertexBuffer::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

} // namespace engine::renderer