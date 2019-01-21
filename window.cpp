#include "window.h"

#include <iostream>

glm::vec2 Window::geometry() const
{
    return _geometry;
}

Window::Window(const std::string& name, const uint width, const uint height,
               const int xPos, const int yPos)
{
    init(name, width, height, xPos, yPos);
}

Window::Window()
{
}

Window::~Window()
{
}

void Window::init(const std::string& name, const uint width, const uint height,
                  const int xPos, const int yPos)
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_CORE);

    _window = SDL_CreateWindow(name.c_str(), xPos, yPos, width, height,
                               SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    if (_window == nullptr)
    {
        std::cout << "WINDOW::INIT _window is nullptr.\nSDL2 error: "
                  << SDL_GetError() << std::endl;
        throw std::runtime_error("Window error.");
    }
    _glcontext = SDL_GL_CreateContext(_window);
    SDL_GL_MakeCurrent(_window, _glcontext);

    // Initialize GLEW to setup the OpenGL Function pointers
    glewExperimental = GL_TRUE;
    glewInit();

    // Define the viewport dimensions
    glViewport(0, 0, width, height);
    // Setup some OpenGL options
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    _geometry = glm::vec2(width, height);
}

void Window::swapBuffer()
{
    SDL_GL_SwapWindow(_window);
}
