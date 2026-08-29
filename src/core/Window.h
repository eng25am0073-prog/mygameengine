#pragma once

#include <string>

struct GLFWwindow;

namespace engine {

class Window {
public:
    Window(std::string title, int width, int height);
    ~Window();

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    bool IsValid() const;

    bool ShouldClose() const;
    void RequestClose();
    void PollEvents();
    void SwapBuffers();
    void SetVsync(bool enabled);

    GLFWwindow* GetNativeWindow() const { return m_handle; }

    int GetWidth() const { return m_width; }
    int GetHeight() const { return m_height; }
    void GetFramebufferSize(int& width, int& height) const;

private:
    static void OnGlfwError(int errorCode, const char* description);

    GLFWwindow* m_handle = nullptr;
    bool m_glfwInitialized = false;
    std::string m_title;
    int m_width;
    int m_height;
};

} // namespace engine