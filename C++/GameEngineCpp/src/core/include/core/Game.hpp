#pragma once

#include <string>
#include <functional>

#include <glad/glad.h>
#include <GLFW/glfw3.h>


namespace GameEngine::Core {

class Game
{
    GLFWwindow* _window = nullptr;
    std::function<void()> Update;
    std::function<void()> Render;
    bool shutdownRequested = false;

    bool ShouldShutdown() const;

public:
    std::string title = "Empty Game";
    int width = 800;
    int height = 600;

    Game() = default;
    Game(std::string title);
    Game(std::string title, int width, int height);
    ~Game();

    ///
    /// @return true on initialization success, false otherwise
    bool Init();
    void Loop(const std::function<void()>& updateFunc, const std::function<void()>& renderFunc);
    void Shutdown();

    /// request the shutdown of the game, triggers the shutdown behaviours including:
    ///  - closing all related threads
    ///  - closing windows and freeing memory
    void RequestShutdown();

    /// should be used with caution
    /// @return the underlying GLFWwindow struct
    GLFWwindow* GetWindow();
};

}
