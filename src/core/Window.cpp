#include "core/Window.h"
#include "core/Log.h"

#include <utility>

#include <GLFW/glfw3.h>

namespace engine {

namespace {

constexpr int kDefaultWidth = 1280;
constexpr int kDefaultHeight = 720;

} // namespace

Window::Window(std::string title, int width, int height)
    : m_title(std::move(title))
    , m_width(width > 0 ? width : kDefaultWidth)
    , m_height(height > 0 ? height : kDefaultHeight)
{
    glfwSetErrorCallback(&Window::OnGlfwError);

    if (!glfwInit()) {
        Log::Error("Failed to initialize GLFW.");
        return;
    }
    m_glfwInitialized = true;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_handle = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);
    if (!m_handle) {
        Log::Error("Failed to create GLFW window.");
        return;
    }

    glfwMakeContextCurrent(m_handle);
    SetVsync(true);

    Log::Info("Created window '" + m_title + "' (" + std::to_string(m_width) + "x" +
              std::to_string(m_height) + ").");
}

Window::~Window()
{
    if (m_handle) {
        glfwDestroyWindow(m_handle);
        m_handle = nullptr;
    }
    if (m_glfwInitialized) {
        glfwTerminate();
        m_glfwInitialized = false;
    }
    Log::Info("Window shut down cleanly.");
}

bool Window::IsValid() const
{
    return m_handle != nullptr;
}

bool Window::ShouldClose() const
{
    return m_handle ? glfwWindowShouldClose(m_handle) != 0 : true;
}

void Window::PollEvents()
{
    if (m_handle) {
        glfwPollEvents();
    }
}

void Window::SwapBuffers()
{
    if (m_handle) {
        glfwSwapBuffers(m_handle);
    }
}

void Window::SetVsync(bool enabled)
{
    glfwSwapInterval(enabled ? 1 : 0);
}

void Window::GetFramebufferSize(int& width, int& height) const
{
    if (m_handle) {
        glfwGetFramebufferSize(m_handle, &width, &height);
        return;
    }
    width = m_width;
    height = m_height;
}

void Window::OnGlfwError(int errorCode, const char* description)
{
    Log::Error("GLFW error " + std::to_string(errorCode) + ": " + description);
}

} // namespace engine