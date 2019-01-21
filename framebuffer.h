#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <GL/glew.h>

#include "texture.h"

class FrameBuffer
{
public:
    GLuint ID;

    Texture colorBuffer;
    Texture depthStencilBuffer;

    FrameBuffer(const GLuint width, const GLuint height);
    ~FrameBuffer();
    void bind() const;
    void unBind() const;
};

#endif // FRAMEBUFFER_H
