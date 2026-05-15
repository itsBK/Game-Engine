#include "include/core/Game.hpp"

using namespace GameEngine::Core;


Game::Game(std::string title)
    : title(std::move(title)) {}

Game::Game(std::string title, int width, int height)
    : title(std::move(title)), width(width), height(height) {}

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
    while (!ShouldShutdown())
    {
        updateFunc();
        renderFunc();

        /* Swap front and back buffers */
        glfwSwapBuffers(_window);
        /* Poll for and process events */
        glfwPollEvents();
    }
    Shutdown();
}

bool Game::ShouldShutdown() const
{
    return shutdownRequested || glfwWindowShouldClose(_window);
}

void Game::RequestShutdown()
{
    shutdownRequested = true;
}

void Game::Shutdown()
{
    glfwDestroyWindow(_window);
    glfwTerminate();
}

GLFWwindow* Game::GetWindow()
{
    return _window;
}
