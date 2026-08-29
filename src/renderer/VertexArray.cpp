#include "renderer/VertexArray.h"
#include "renderer/VertexBuffer.h"

#include <glad/gl.h>

namespace engine::renderer {

namespace {

unsigned int GLTypeFromShaderDataType(ShaderDataType type)
{
    switch (type) {
    case ShaderDataType::Float:
    case ShaderDataType::Float2:
    case ShaderDataType::Float3:
    case ShaderDataType::Float4:
        return GL_FLOAT;
    }
    return 0;
}

} // namespace

void VertexArray::Create()
{
    glGenVertexArrays(1, &m_arrayId);
}

void VertexArray::Destroy()
{
    if (m_arrayId != 0) {
        glDeleteVertexArrays(1, &m_arrayId);
        m_arrayId = 0;
    }
}

void VertexArray::AddVertexBuffer(const VertexBuffer& buffer, const BufferLayout& layout)
{
    Bind();
    buffer.Bind();

    const auto& elements = layout.GetElements();
    std::size_t stride = layout.GetStride();

    unsigned int index = 0;
    for (const BufferElement& element : elements) {
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(
            index,
            static_cast<GLint>(ShaderDataTypeComponentCount(element.type)),
            GLTypeFromShaderDataType(element.type),
            element.normalized ? GL_TRUE : GL_FALSE,
            static_cast<GLsizei>(stride),
            reinterpret_cast<const void*>(element.offset));
        ++index;
    }

    buffer.Unbind();
    Unbind();
}

void VertexArray::Bind() const
{
    glBindVertexArray(m_arrayId);
}

void VertexArray::Unbind() const
{
    glBindVertexArray(0);
}

} // namespace engine::renderer