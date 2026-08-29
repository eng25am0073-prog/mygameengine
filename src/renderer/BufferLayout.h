#pragma once

#include <cstddef>
#include <vector>

namespace engine::renderer {

enum class ShaderDataType {
    Float,
    Float2,
    Float3,
    Float4
};

std::size_t ShaderDataTypeSize(ShaderDataType type);
unsigned int ShaderDataTypeComponentCount(ShaderDataType type);

struct BufferElement {
    ShaderDataType type;
    bool normalized;
    std::size_t offset;
};

class BufferLayout {
public:
    BufferLayout() = default;

    void Push(ShaderDataType type, bool normalized = false);

    const std::vector<BufferElement>& GetElements() const { return m_elements; }
    std::size_t GetStride() const { return m_stride; }

private:
    std::vector<BufferElement> m_elements;
    std::size_t m_stride = 0;
};

} // namespace engine::renderer