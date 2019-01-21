#ifndef APPLICATION_H
#define APPLICATION_H

#include <memory>
#include <stack>

#include "statebase.h"
#include "window.h"

class Application
{
private:
    std::stack<std::unique_ptr<StateBase>> _states;
    void limitFPS();
    float calcDeltaTime();
    bool _isLimitingFps;
    float _fpsLimit;
    bool isRunning;

public:
    Window window;

    Application(const std::string& title, const uint windowX = 800,
                const uint windowY = 600);

    void mainLoop();
    void pushState(std::unique_ptr<StateBase> state);
    void popState();
    void changeState(std::unique_ptr<StateBase> state);

    //    Window window() const;
};
#endif // APPLICATION_H
