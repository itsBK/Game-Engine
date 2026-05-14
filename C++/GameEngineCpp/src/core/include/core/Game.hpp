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

public:
    std::string title = "Empty Game";
    int width = 800;
    int height = 600;

    Game() = default;
    explicit Game(std::string&& title);
    Game(std::string&& title, int width, int height);
    ~Game();

    ///
    /// @return true on initialization success, false otherwise
    bool Init();
    void Loop(const std::function<void()>& updateFunc, const std::function<void()>& renderFunc);
    void Shutdown();

    /// should be used with caution
    /// @return the underlaying GLFWwindow struct
    GLFWwindow* GetWindow() const;
};

}
