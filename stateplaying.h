#ifndef STATEPLAYING_H
#define STATEPLAYING_H

#include "application.h"
#include "camera2d.h"
#include "cellrenderer.h"
#include "framebuffer.h"
#include "shader.h"
#include "simplerenderer.h"
#include "statebase.h"
#include "grid.h"

class StatePlaying : public StateBase
{
private:
    Grid _grid;
    Camera2D _mainCamera;
    CellWorld _cellWorld;
    CellRenderer _cellRenderer;
    SimpleRenderer _simpleRenderer;
    Shader _quadShader;
    Shader _lineShader;
    FrameBuffer _fb;
    bool _simulating;

    const unsigned int worldXSize = 50;
    const unsigned int worldYSize = 50;


public:
    StatePlaying(Application& app);
    void input(float deltaTime);
    void update(float deltaTime);
    void preDraw();
    void draw();
    void postDraw();
};

#endif // STATEPLAYING_H
