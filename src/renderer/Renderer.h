#pragma once

namespace engine::renderer {

class Shader;
class VertexArray;

class Renderer {
public:
    static void SetClearColor(float r, float g, float b, float a);
    static void Clear();
    static void Draw(const VertexArray& vertexArray, const Shader& shader, unsigned int vertexCount);
};

} // namespace engine::renderer