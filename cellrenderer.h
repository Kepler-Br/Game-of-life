#ifndef CELLRENDERER_H
#define CELLRENDERER_H

#include <vector>

#include "camera2d.h"
#include "cell.h"
#include "cellworld.h"
#include "shader.h"

// class Cell;

class CellRenderer
{
private:
    //    std::vector<Cell*> _cells;
    Camera2D* _mainCamera;
    GLuint _vertexArrayID;
    GLuint _vertexbuffer;
    Shader _cellShader;

public:
    CellRenderer(Camera2D& camera);
    void draw(const Cell& cell, uint currentGeneration);
};

#endif // CELLRENDERER_H
