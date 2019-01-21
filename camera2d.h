#ifndef CAMERA2D_H
#define CAMERA2D_H

#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>

#include <GL/glew.h>
#include <iostream>

class Camera2D
{
private:
    bool _matrixChanged;
    GLuint _width;
    GLuint _height;
    GLfloat _scale;
    glm::vec2 _position;
    glm::mat4 _cameraMatrix;
    glm::mat4 _orthoMatrix;

public:
    Camera2D();
    void init(GLuint width, GLuint height);
    void update();

    glm::vec2 convertScreenToWorld(glm::vec2 screenCoords);

    void addPosition(const glm::vec2& position)
    {
        _position += position;
        _matrixChanged = true;
    }
    void addScale(float scale);

    // setters
    void setPosition(const glm::vec2& position)
    {
        _position = position;
        _matrixChanged = true;
    }
    void setScale(float scale)
    {
        _scale = scale;
        _matrixChanged = true;
    }

    // getters
    const glm::vec2& getPosition() const
    {
        return _position;
    }
    float getScale() const
    {
        return _scale;
    }
    const glm::mat4& getCameraMatrix() const
    {
        return _cameraMatrix;
    }
    float getAspectRatio() const
    {
        return (float)_width / (float)_height;
    }
};

#endif // CAMERA2D_H
