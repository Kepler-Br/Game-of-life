#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>

#include <GL/glew.h>
#include <glm/vec2.hpp>

#include <string>

class Window
{
private:
    SDL_Window* _window = nullptr;
    SDL_GLContext _glcontext = NULL;
    glm::vec2 _geometry;

public:
    Window(const std::string& name, const uint width = 800,
           const uint height = 600, const int xPos = 0, const int yPos = 0);
    Window();
    virtual ~Window();

    void init(const std::string& name, const uint width = 800,
              const uint height = 600, const int xPos = 0, const int yPos = 0);
    void swapBuffer();

    glm::vec2 geometry() const;
};
#endif // WINDOW_H
