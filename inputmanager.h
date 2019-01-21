#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <map>

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>

class InputManager
{
private:
    // Key state of current frame.
    static std::map<GLuint, bool> keyMap;
    // Key state of previous frame.
    static std::map<GLuint, bool> prevKeyMap;
    static std::map<GLuint, bool> events;
    static glm::ivec2 relativeMouseCoord;
    static glm::ivec2 globalMouseCoord;
    static glm::ivec2 deltaMouseCoord;

    static bool wasKeyDown(GLuint keyID);
    static void pressEvent(GLuint eventID);
    static void updateState();

public:
    static void update();

    static void pressKey(GLuint keyID);
    static void releaseKey(GLuint keyID);

    // Gets.
    static glm::ivec2 getDeltaMouseCoord();
    static glm::ivec2 getRelativeMouseCoord();
    static glm::ivec2 getGlobalMouseCoord();

    static bool isKeyDown(GLuint keyID);
    static bool isKeyReleased(GLuint keyID);
    static bool isKeyPressed(GLuint keyID);
    static bool isEventPending(GLuint eventID);
};
#endif // INPUTMANAGER_H
