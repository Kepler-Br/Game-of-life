#include "grid.h"


#include <vector>

#include "resourcemanager.h"

Grid::Grid()
{
}

void Grid::init(int sizeX, int sizeY)
{
    _lineShader =
      ResourceManager::getShader("./Shaders/line.vert", "./Shaders/line.frag");
    std::vector<GLfloat> grid;
    grid.reserve(sizeX*4+sizeY*4);
    for (int x = 0; x <= sizeX; x++)
    {
        grid.push_back(x);
        grid.push_back(0.0f);
        grid.push_back(x);
        grid.push_back(sizeY);
    }
    for (int y = 0; y <= sizeY; y++)
    {
        grid.push_back(0.0f);
        grid.push_back(y);
        grid.push_back(sizeX);
        grid.push_back(y);
    }

    glGenVertexArrays(1, &_gridVAO);
    glGenBuffers(1, &_gridVBO);
    glBindVertexArray(_gridVAO);
    glBindBuffer(GL_ARRAY_BUFFER, _gridVBO);
    glBufferData(GL_ARRAY_BUFFER, grid.size() * 4, &grid[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    glBindVertexArray(0);
    _vertices = grid.size();
}

void Grid::draw(Camera2D& camera)
{
    _lineShader.use();
    _lineShader.setUniform("cameraMatrix", camera.getCameraMatrix());
    glBindVertexArray(_gridVAO);
    glEnableVertexAttribArray(0);
    glDrawArrays(GL_LINES, 0, _vertices);
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
}
