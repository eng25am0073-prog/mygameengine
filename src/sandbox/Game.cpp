#include "sandbox/Game.h"

#include "core/Log.h"
#include "renderer/BufferLayout.h"
#include "renderer/Renderer.h"
#include "renderer/Shader.h"
#include "renderer/VertexArray.h"
#include "renderer/VertexBuffer.h"

namespace engine {

namespace {

constexpr const char* kVertexShaderSource = R"(
#version 330 core

layout(location = 0) in vec3 aPosition;

void main() {
    gl_Position = vec4(aPosition, 1.0);
}
)";

constexpr const char* kFragmentShaderSource = R"(
#version 330 core

out vec4 fragColor;

uniform vec3 uColor;

void main() {
    fragColor = vec4(uColor, 1.0);
}
)";

} // namespace

Game::Game() = default;

Game::~Game() = default;

void Game::OnStart()
{
    Log::Info("Game started.");

    m_shader = std::make_unique<renderer::Shader>();
    if (!m_shader->Create(kVertexShaderSource, kFragmentShaderSource)) {
        Log::Error("Failed to create triangle shader.");
        m_shader.reset();
        return;
    }

    const float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f,
    };

    renderer::BufferLayout layout;
    layout.Push(renderer::ShaderDataType::Float3);

    m_vertexBuffer.Create(vertices, sizeof(vertices));
    m_vertexArray.Create();
    m_vertexArray.AddVertexBuffer(m_vertexBuffer, layout);

    m_shader->Bind();
    m_shader->SetUniformVec3("uColor", 1.0f, 0.5f, 0.2f);

    renderer::Renderer::SetClearColor(0.1f, 0.1f, 0.1f, 1.0f);
}

void Game::OnRender()
{
    renderer::Renderer::Clear();
    renderer::Renderer::Draw(m_vertexArray, *m_shader, 3);
}

void Game::OnShutdown()
{
    m_vertexArray.Destroy();
    m_vertexBuffer.Destroy();
    if (m_shader) {
        m_shader->Destroy();
        m_shader.reset();
    }
    Log::Info("Game shut down.");
}

} // namespace engine