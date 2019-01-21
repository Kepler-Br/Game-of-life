#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include <glm/vec2.hpp>

struct Texture
{
    GLuint ID = 0;
    glm::vec2 geometry;
};
#endif // TEXTURE_H
