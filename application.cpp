#include "application.h"

//#include "stateplaying.h"
#include "inputmanager.h"
#include "window.h"

void Application::limitFPS()
{
    static uint start = SDL_GetTicks();
    if (_isLimitingFps && 1000 / _fpsLimit > SDL_GetTicks() - start)
    {
        SDL_Delay(1000 / _fpsLimit - (SDL_GetTicks() - start));
    }
    start = SDL_GetTicks();
}

float Application::calcDeltaTime()
{
    static float lastTime = 0;
    static float currentTime = 0;

    if (currentTime > lastTime)
        lastTime = currentTime;
    currentTime = SDL_GetTicks();
    return ((currentTime - lastTime) / 1000.0f);
}

Application::Application(const std::__cxx11::string& title, const uint windowX,
                         const uint windowY)
{
    window.init(title, windowX, windowY);
    _isLimitingFps = true;
    _fpsLimit = 60.0f;
    isRunning = true;
    //    pushState(std::move(startState));
}

void Application::mainLoop()
{
    while (isRunning)
    {
        float deltaTime = calcDeltaTime();

        InputManager::update();

        _states.top()->input(deltaTime);
        _states.top()->update(deltaTime);

        _states.top()->preDraw();
        _states.top()->draw();
        _states.top()->postDraw();

        if (InputManager::isEventPending(SDL_QUIT))
            break;
    }
}

void Application::pushState(std::unique_ptr<StateBase> state)
{
    _states.push(std::move(state));
}

void Application::popState()
{
    _states.pop();
}

void Application::changeState(std::unique_ptr<StateBase> state)
{
    popState();
    pushState(std::move(state));
}
