#include "core/Application.h"
#include "core/Input.h"
#include "core/Log.h"
#include "core/Window.h"

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <chrono>

namespace engine {

namespace {

constexpr const char* kWindowTitle = "Engine";
constexpr int kWindowWidth = 1280;
constexpr int kWindowHeight = 720;

} // namespace

Application::Application() = default;

Application::~Application() = default;

void Application::Run()
{
    Log::Info("Engine starting.");

    m_window = std::make_unique<Window>(kWindowTitle, kWindowWidth, kWindowHeight);
    if (!m_window->IsValid()) {
        Log::Error("Window creation failed; engine cannot start.");
        m_window.reset();
        return;
    }
    input::Initialize(m_window->GetNativeWindow());

    if (!gladLoadGL(reinterpret_cast<GLADloadfunc>(glfwGetProcAddress))) {
        Log::Error("Failed to initialize OpenGL functions (GLAD).");
        return;
    }
    if (!GLAD_GL_VERSION_3_3) {
        Log::Error("OpenGL 3.3 is not available on this system.");
        return;
    }

    std::string glVersion(reinterpret_cast<const char*>(glGetString(GL_VERSION)));
    std::string glRenderer(reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
    Log::Info("OpenGL " + glVersion + " (" + glRenderer + ")");

    int framebufferWidth = 0;
    int framebufferHeight = 0;
    m_window->GetFramebufferSize(framebufferWidth, framebufferHeight);
    glViewport(0, 0, framebufferWidth, framebufferHeight);

    OnStart();
    m_isRunning = true;

    auto previousTime = std::chrono::steady_clock::now();

    while (m_window && !m_window->ShouldClose()) {
        auto currentTime = std::chrono::steady_clock::now();
        float deltaTime = std::chrono::duration<float>(currentTime - previousTime).count();
        previousTime = currentTime;

        m_window->PollEvents();

        if (input::IsKeyPressed(input::Key::Escape)) {
            m_window->RequestClose();
        }

        OnUpdate(deltaTime);
        OnRender();

        m_window->SwapBuffers();
    }

    m_isRunning = false;
    OnShutdown();

    Log::Info("Engine stopped.");
    m_window.reset();
}

} // namespace engine