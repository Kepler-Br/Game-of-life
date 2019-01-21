#ifndef SHADER_H
#define SHADER_H

#include <string>

#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

#include "texture.h"

class Shader
{
public:
    GLuint ID;

    Shader();
    void use() const;
    GLuint getShaderID() const;
    GLuint getUniformID(const std::string& name) const;
    void setUniform(const std::string& name, const GLfloat value);
    void setUniform(const std::string& name, const GLint value);
    void setUniform(const std::string& name, const GLuint value);
    void setUniform(const std::string& name, const glm::mat4& value,
                    const GLsizei arrayCount = 1, const bool transpose = false);
    void setUniform(const std::string& name, const glm::vec3& value,
                    const GLsizei arrayCount = 1);
    void setUniform(const std::string& name, const glm::vec2& value,
                    const GLsizei arrayCount = 1);
    void setTexture(const std::string& name, const GLuint textureID,
                    const GLuint& textureNumber = 0);
    void setTexture(const std::string& name, const Texture& texture,
                    const GLuint& textureNumber = 0);
};
#endif // SHADER_H
