#include "shader.h"

Shader::Shader()
{
}

void Shader::use() const
{
    glUseProgram(ID);
}

GLuint Shader::getUniformID(const std::__cxx11::string& name) const
{
    return glGetUniformLocation(ID, name.c_str());
}

void Shader::setUniform(const std::string& name, const GLfloat value)
{
    GLuint ID = getUniformID(name);
    glUniform1f(ID, value);
}

void Shader::setUniform(const std::string& name, const GLint value)
{
    GLuint ID = getUniformID(name);
    glUniform1i(ID, value);
}

void Shader::setUniform(const std::string& name, const GLuint value)
{
    GLuint ID = getUniformID(name);
    glUniform1ui(ID, value);
}

void Shader::setUniform(const std::string& name, const glm::mat4& value,
                        const GLsizei arrayCount, const bool transpose)
{
    GLuint ID = getUniformID(name);
    glUniformMatrix4fv(ID, arrayCount, transpose, &value[0][0]);
}

void Shader::setUniform(const std::__cxx11::string& name,
                        const glm::vec3& value, const GLsizei arrayCount)
{
    GLuint ID = getUniformID(name);
    glUniform3fv(ID, arrayCount, &value[0]);
}

void Shader::setUniform(const std::__cxx11::string &name, const glm::vec2 &value, const GLsizei arrayCount)
{
    GLuint ID = getUniformID(name);
    glUniform2fv(ID, arrayCount, &value[0]);
}

void Shader::setTexture(const std::string& name, const GLuint textureID,
                        const GLuint& textureNumber)
{
    GLuint ID = getUniformID(name);

    glUniform1i(ID, textureNumber);

    glActiveTexture(GL_TEXTURE0 + textureNumber);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glActiveTexture(GL_TEXTURE0);
}

void Shader::setTexture(const std::string& name, const Texture& texture,
                        const GLuint& textureNumber)
{
    GLuint ID = getUniformID(name);

    glUniform1i(ID, textureNumber);

    glActiveTexture(GL_TEXTURE0 + textureNumber);
    glBindTexture(GL_TEXTURE_2D, texture.ID);
    glActiveTexture(GL_TEXTURE0);
}
