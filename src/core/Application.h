#pragma once

#include <memory>

namespace engine {

class Window;

class Application {
public:
    Application();
    virtual ~Application();

    void Run();

protected:
    virtual void OnStart() {}
    virtual void OnUpdate(float) {}
    virtual void OnRender() {}
    virtual void OnShutdown() {}

private:
    std::unique_ptr<Window> m_window;
    bool m_isRunning = false;
};

} // namespace engine