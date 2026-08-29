#pragma once

struct GLFWwindow;

namespace engine::input {

namespace Key {
constexpr int Escape = 256;
constexpr int Left = 263;
constexpr int Right = 262;
constexpr int Up = 265;
constexpr int Down = 264;
constexpr int W = 87;
constexpr int A = 65;
constexpr int S = 83;
constexpr int D = 68;
} // namespace Key

void Initialize(GLFWwindow* window);

bool IsKeyPressed(int keyCode);

} // namespace engine::input