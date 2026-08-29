#include "renderer/BufferLayout.h"

namespace engine::renderer {

std::size_t ShaderDataTypeSize(ShaderDataType type)
{
    switch (type) {
    case ShaderDataType::Float:  return sizeof(float) * 1;
    case ShaderDataType::Float2: return sizeof(float) * 2;
    case ShaderDataType::Float3: return sizeof(float) * 3;
    case ShaderDataType::Float4: return sizeof(float) * 4;
    }
    return 0;
}

unsigned int ShaderDataTypeComponentCount(ShaderDataType type)
{
    switch (type) {
    case ShaderDataType::Float:  return 1;
    case ShaderDataType::Float2: return 2;
    case ShaderDataType::Float3: return 3;
    case ShaderDataType::Float4: return 4;
    }
    return 0;
}

void BufferLayout::Push(ShaderDataType type, bool normalized)
{
    BufferElement element;
    element.type = type;
    element.normalized = normalized;
    element.offset = m_stride;
    m_elements.push_back(element);
    m_stride += ShaderDataTypeSize(type);
}

} // namespace engine::renderer