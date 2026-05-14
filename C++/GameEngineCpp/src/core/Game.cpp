#include "include/core/Game.hpp"

using namespace GameEngine::Core;


Game::Game(const std::string& title)
    : title(title) {}

Game::Game(const std::string& title, int width, int height)
    : title(title), width(width), height(height) {}

Game::~Game() = default;


bool Game::Init()
{
    if (!glfwInit())
    {
        //TODO: log
        return false;
    }

    /* Create a windowed mode window and its OpenGL context */
    _window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!_window)
    {
        //TODO: log
        glfwTerminate();
        return false;
    }

    // TODO: log
    /* Make the window's context current */
    glfwMakeContextCurrent(_window);
    gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));

    //TODO: log
    return true;
}

void Game::Loop(const std::function<void()>& updateFunc, const std::function<void()>& renderFunc)
{
    //TODO: encapsulate shouldClose func
    while (!glfwWindowShouldClose(_window))
    {
        updateFunc();
        renderFunc();

        /* Swap front and back buffers */
        glfwSwapBuffers(_window);
        /* Poll for and process events */
        glfwPollEvents();
    }
}

void Game::Shutdown()
{
    glfwDestroyWindow(_window);
    glfwTerminate();
}

GLFWwindow* Game::GetWindow() const
{
    return _window;
}

