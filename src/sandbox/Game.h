#pragma once

#include "core/Application.h"
#include "renderer/VertexArray.h"
#include "renderer/VertexBuffer.h"

#include <memory>

namespace engine::renderer {
class Shader;
}

namespace engine {

class Game final : public Application {
public:
    Game();
    ~Game();

protected:
    void OnStart() override;
    void OnRender() override;
    void OnShutdown() override;

private:
    std::unique_ptr<renderer::Shader> m_shader;
    renderer::VertexArray m_vertexArray;
    renderer::VertexBuffer m_vertexBuffer;
};

} // namespace engine