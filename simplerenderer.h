#ifndef SIMPLERENDERER_H
#define SIMPLERENDERER_H

#include <vector>

#include "camera2d.h"

class SimpleRenderer
{
private:
    Camera2D* _mainCamera;
    GLuint _quadVAO;
    GLuint _quadVBO;
    GLuint _lineVAO;
    GLuint _lineVBO;

public:
    SimpleRenderer();
    void quad();
    void verticalLine();
};


#endif // SIMPLERENDERER_H
