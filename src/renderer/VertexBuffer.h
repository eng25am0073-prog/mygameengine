#pragma once

#include <cstddef>

namespace engine::renderer {

class VertexBuffer {
public:
    VertexBuffer() = default;
    ~VertexBuffer() = default;

    VertexBuffer(const VertexBuffer&) = delete;
    VertexBuffer& operator=(const VertexBuffer&) = delete;

    void Create(const void* data, std::size_t size);
    void Destroy();

    void Bind() const;
    void Unbind() const;

private:
    unsigned int m_bufferId = 0;
};

} // namespace engine::renderer