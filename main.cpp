#include <iostream>
#include <memory>
#include "application.h"
#include "stateplaying.h"

int main(int argc, char *argv[])
{
    try
    {
        Application app("Conway's game of life", 800, 800);
        app.pushState(std::make_unique<StatePlaying>(app));
        app.mainLoop();
    }
    catch (...)
    {
        exit(1);
    }
    return 0;
}
