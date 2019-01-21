#include "cellrenderer.h"
#include "resourcemanager.h"
#include <GL/glew.h>

// *& - a reference to a pointer.
CellRenderer::CellRenderer(Camera2D& camera)
{
    _mainCamera = &camera;
    _cellShader = ResourceManager::getShader("./Shaders/cellShader.vert",
                                             "./Shaders/cellShader.frag");
    glGenVertexArrays(1, &_vertexArrayID);
    glBindVertexArray(_vertexArrayID);
//    const GLfloat g_vertex_buffer_data[] = {
//        -0.5f, -0.5f, 0.0f,
//        0.5f, -0.5f, 0.0f,
//        -0.5f, 0.5f,  0.0f,
//        0.5f, 0.5f,  0.0f,
//    };
    const GLfloat g_vertex_buffer_data[] = {
       0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 0.0f
    };
    // Generate 1 buffer, put the resulting identifier in vertexbuffer
    glGenBuffers(1, &_vertexbuffer);
    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, _vertexbuffer);
    // Give our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data),
                 g_vertex_buffer_data, GL_STATIC_DRAW);
    // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, _vertexbuffer);
    glVertexAttribPointer(0, // attribute 0. No particular reason for 0, but
                             // must match the layout in the shader.
                          3, // size
                          GL_FLOAT, // type
                          GL_FALSE, // normalized?
                          0,        // stride
                          (void*)0  // array buffer offset
                          );
    // Draw the triangle !
    glDisableVertexAttribArray(0);
}

void CellRenderer::draw(const Cell& cell, uint currentGeneration)
{
    _cellShader.use();
    _cellShader.setUniform("cameraMatrix", (*_mainCamera).getCameraMatrix());
    _cellShader.setUniform("generation", cell.generation);
    _cellShader.setUniform("currentGeneration", currentGeneration);
    _cellShader.setUniform("cellX", cell.x);
    _cellShader.setUniform("cellY", cell.y);
    glBindVertexArray(_vertexArrayID);
    glEnableVertexAttribArray(0);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
}
