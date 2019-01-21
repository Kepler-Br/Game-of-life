#include "simplerenderer.h"
#include "resourcemanager.h"
#include <GL/glew.h>

// *& - a reference to a pointer.
SimpleRenderer::SimpleRenderer()
{
    {
    GLfloat quadVertices[] = {   // Vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
                                 // Positions   // TexCoords
                                 -1.0f,  1.0f,  0.0f, 1.0f,
                                 -1.0f, -1.0f,  0.0f, 0.0f,
                                 1.0f, -1.0f,  1.0f, 0.0f,

                                 -1.0f,  1.0f,  0.0f, 1.0f,
                                 1.0f, -1.0f,  1.0f, 0.0f,
                                 1.0f,  1.0f,  1.0f, 1.0f
                             };

    glGenVertexArrays(1, &_quadVAO);
    glGenBuffers(1, &_quadVBO);
    glBindVertexArray(_quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, _quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
    glBindVertexArray(0);
    }
    {
    GLfloat quadVertices[] = {   // Vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
                                 // Positions   // TexCoords
                                 0.0f,  -1.0f,
                                 0.0f, 1.0f,
                             };

    glGenVertexArrays(1, &_lineVAO);
    glGenBuffers(1, &_lineVBO);
    glBindVertexArray(_lineVAO);
    glBindBuffer(GL_ARRAY_BUFFER, _lineVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    glBindVertexArray(0);
    }
}

void SimpleRenderer::quad()
{
    glBindVertexArray(_quadVAO);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glBindVertexArray(0);
}

void SimpleRenderer::verticalLine()
{
    glBindVertexArray(_lineVAO);
    glEnableVertexAttribArray(0);
    glDrawArrays(GL_LINES, 0, 2);
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
}
