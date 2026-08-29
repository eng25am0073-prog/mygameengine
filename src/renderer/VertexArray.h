#pragma once

#include "renderer/BufferLayout.h"

namespace engine::renderer {

class VertexBuffer;

class VertexArray {
public:
    VertexArray() = default;
    ~VertexArray() = default;

    VertexArray(const VertexArray&) = delete;
    VertexArray& operator=(const VertexArray&) = delete;

    void Create();
    void Destroy();

    void AddVertexBuffer(const VertexBuffer& buffer, const BufferLayout& layout);

    void Bind() const;
    void Unbind() const;

private:
    unsigned int m_arrayId = 0;
};

} // namespace engine::renderer