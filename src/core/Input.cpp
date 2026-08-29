#include "core/Input.h"

#include <GLFW/glfw3.h>

namespace engine::input {

namespace {

GLFWwindow* s_activeWindow = nullptr;

} // namespace

void Initialize(GLFWwindow* window)
{
    s_activeWindow = window;
}

bool IsKeyPressed(int keyCode)
{
    if (!s_activeWindow) {
        return false;
    }
    return glfwGetKey(s_activeWindow, keyCode) == GLFW_PRESS;
}

} // namespace engine::input