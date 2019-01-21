#ifndef GRID_H
#define GRID_H

#include <GL/glew.h>

#include "shader.h"
#include "camera2d.h"

class Grid
{
private:
    GLuint _gridVBO, _gridVAO;
    Shader _lineShader;
    GLuint _vertices;

public:
    Grid();
    void init(int sizeX, int sizeY);
    void draw(Camera2D &camera);
};


#endif // GRID_H
