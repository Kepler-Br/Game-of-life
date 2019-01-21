#include "framebuffer.h"
#include <iostream>

FrameBuffer::FrameBuffer(const GLuint width, const GLuint height)
{
    glGenFramebuffers(1, &ID);
    glBindFramebuffer(GL_FRAMEBUFFER, ID);
    {
        // Gen color buffer
        glGenTextures(1, &colorBuffer.ID);
        colorBuffer.geometry = glm::vec2(width, height);

        glBindTexture(GL_TEXTURE_2D, colorBuffer.ID);
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                         GL_UNSIGNED_BYTE, NULL);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                            GL_CLAMP_TO_BORDER);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
                            GL_CLAMP_TO_BORDER);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                                   GL_TEXTURE_2D, colorBuffer.ID, 0);

        }
        glBindTexture(GL_TEXTURE_2D, 0);

        // Gen depth buffer
        glGenTextures(1, &depthStencilBuffer.ID);
        depthStencilBuffer.geometry = glm::vec2(width, height);

        glBindTexture(GL_TEXTURE_2D, depthStencilBuffer.ID);
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, width, height,
                         0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                            GL_CLAMP_TO_BORDER);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
                            GL_CLAMP_TO_BORDER);

            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,
                                   GL_TEXTURE_2D, depthStencilBuffer.ID, 0);
        }
    }

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout << "Framebuffer is not complete.";
        throw std::runtime_error("Framebuffer is not complete.");
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

FrameBuffer::~FrameBuffer()
{
    glDeleteFramebuffers(1, &ID);
}

void FrameBuffer::bind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, ID);
}

void FrameBuffer::unBind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
