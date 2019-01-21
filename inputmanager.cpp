#include "inputmanager.h"
#include <iostream>

// Key state of current frame.
std::map<GLuint, bool> InputManager::keyMap;
// Key state of previous frame.
std::map<GLuint, bool> InputManager::prevKeyMap;
std::map<GLuint, bool> InputManager::events;
glm::ivec2 InputManager::relativeMouseCoord;
glm::ivec2 InputManager::globalMouseCoord;
glm::ivec2 InputManager::deltaMouseCoord;

bool InputManager::wasKeyDown(GLuint keyID)
{
    auto it = prevKeyMap.find(keyID);
    if (it != prevKeyMap.end())
    {
        // Found the key.
        return it->second;
    }
    // Did not found the key.
    return false;
}

void InputManager::pressEvent(GLuint eventID)
{
    events[eventID] = true;
}

void InputManager::updateState()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                pressEvent(SDL_QUIT);
                break;
            case SDL_KEYDOWN:
                pressKey(event.key.keysym.sym);
                break;
            case SDL_KEYUP:
                releaseKey(event.key.keysym.sym);
                break;
            case SDL_MOUSEBUTTONDOWN:
                pressKey(event.button.button);
                break;
            case SDL_MOUSEBUTTONUP:
                releaseKey(event.button.button);
                break;
        }
    }
}

void InputManager::update()
{
    SDL_GetRelativeMouseState(&deltaMouseCoord.x, &deltaMouseCoord.y);
    //    for(auto it:keyMap)
    for (auto it = keyMap.begin(); it != keyMap.end(); it++)
    {
        prevKeyMap[it->first] = it->second;
    }
    updateState();
}

void InputManager::pressKey(GLuint keyID)
{
    keyMap[keyID] = true;
}

void InputManager::releaseKey(GLuint keyID)
{
    keyMap[keyID] = false;
}

glm::ivec2 InputManager::getDeltaMouseCoord()
{
    return deltaMouseCoord;
}

glm::ivec2 InputManager::getRelativeMouseCoord()
{
    SDL_GetMouseState(&relativeMouseCoord.x, &relativeMouseCoord.y);
    return relativeMouseCoord;
}

glm::ivec2 InputManager::getGlobalMouseCoord()
{
    SDL_GetGlobalMouseState(&globalMouseCoord.x, &globalMouseCoord.y);
    return globalMouseCoord;
}

bool InputManager::isKeyDown(GLuint keyID)
{
    auto it = keyMap.find(keyID);
    if (it != keyMap.end())
    {
        // Found the key.
        return it->second;
    }
    // Did not found the key.
    return false;
}

bool InputManager::isKeyReleased(GLuint keyID)
{
    if (wasKeyDown(keyID) == true && isKeyDown(keyID) == false)
    {
        return true;
    }
    return false;
}

bool InputManager::isKeyPressed(GLuint keyID)
{
    if (wasKeyDown(keyID) == false && isKeyDown(keyID) == true)
    {
        return true;
    }
    return false;
}

bool InputManager::isEventPending(GLuint eventID)
{
    auto it = events.find(eventID);
    if (it != events.end())
    {
        // Found the key.
        return it->second;
    }
    // Did not found the key.
    return false;
}
