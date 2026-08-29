#include "renderer/Renderer.h"
#include "renderer/Shader.h"
#include "renderer/VertexArray.h"

#include <glad/gl.h>

namespace engine::renderer {

void Renderer::SetClearColor(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
}

void Renderer::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::Draw(const VertexArray& vertexArray, const Shader& shader, unsigned int vertexCount)
{
    shader.Bind();
    vertexArray.Bind();
    glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(vertexCount));
    vertexArray.Unbind();
}

} // namespace engine::renderer