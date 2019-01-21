#ifndef STATEBASE_H
#define STATEBASE_H

#include <memory>
#include <stack>

class Application;

class StateBase
{
protected:
    Application* _app;
    StateBase* _prevState;

public:
    StateBase(Application& app)
      : _app(&app)
      , _prevState(nullptr)
    {
    }
    StateBase(Application& app, StateBase& prevState)
      : _app(&app)
      , _prevState(&prevState)
    {
    }
    virtual ~StateBase()
    {
    }

    virtual void input(float deltaTime) = 0;
    virtual void update(float deltaTime) = 0;
    virtual void preDraw() = 0;
    virtual void draw() = 0;
    virtual void postDraw() = 0;
};
#endif // STATEBASE_H
