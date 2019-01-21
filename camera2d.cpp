#include "camera2d.h"

#include <glm/gtc/matrix_transform.hpp>

Camera2D::Camera2D()
  : _width(800)
  , _height(600)
  , _scale(1.0f)
  , _matrixChanged(true)
  , _position(0.0f, 0.0f)
  , _cameraMatrix(1.0f)
  , _orthoMatrix(1.0f)
{
}

void Camera2D::init(GLuint width, GLuint height)
{
    _width = width;
    _height = height;
    _orthoMatrix = glm::ortho(0.0f, (float)_width, 0.0f, (float)_height);
}

void Camera2D::update()
{
    // Only update if our position or scale have changed
    if (_matrixChanged)
    {
        // Camera Translation
        glm::vec3 translate(-_position.x + _width / 2,
                            -_position.y + _height / 2, 0.0f);
        _cameraMatrix = glm::translate(_orthoMatrix, translate);

        // Camera Scale
        glm::vec3 scale(_scale, _scale, 0.0f);
        _cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * _cameraMatrix;

        _matrixChanged = false;
    }
}

glm::vec2 Camera2D::convertScreenToWorld(glm::vec2 screenCoords)
{
    // Invert Y direction
    screenCoords.y = _height - screenCoords.y;
    // Make it so that 0 is the center
    screenCoords -= glm::vec2(_width / 2, _height / 2);
    // Scale the coordinates
    screenCoords /= _scale;
    // Translate with the camera position
    screenCoords += _position;
    return screenCoords;
}

void Camera2D::addScale(float scale)
{
    _scale += scale;
    if (_scale < 1.0f)
        _scale = 1.0f;
    if (_scale > 20.0f)
        _scale = 20.0f;
    std::cout << _scale << std::endl;
    _matrixChanged = true;
}

//// Simple AABB test to see if a box is in the camera view
// bool Camera2D::isBoxInView(const glm::vec2& position, const glm::vec2&
// dimensions) {

//    glm::vec2 scaledScreenDimensions = glm::vec2(_width, _height) / (_scale);

//    // The minimum distance before a collision occurs
//    const float MIN_DISTANCE_X = dimensions.x / 2.0f +
//    scaledScreenDimensions.x / 2.0f;
//    const float MIN_DISTANCE_Y = dimensions.y / 2.0f +
//    scaledScreenDimensions.y / 2.0f;

//    // Center position of the parameters
//    glm::vec2 centerPos = position + dimensions / 2.0f;
//    // Center position of the camera
//    glm::vec2 centerCameraPos = _position;
//    // Vector from the input to the camera
//    glm::vec2 distVec = centerPos - centerCameraPos;

//    // Get the depth of the collision
//    float xDepth = MIN_DISTANCE_X - abs(distVec.x);
//    float yDepth = MIN_DISTANCE_Y - abs(distVec.y);

//    // If both the depths are > 0, then we collided
//    if (xDepth > 0 && yDepth > 0) {
//        // There was a collision
//        return true;
//    }
//    return false;
//}
