#include "stateplaying.h"
#include "framebuffer.h"
#include "inputmanager.h"
#include "resourcemanager.h"
#include <random>
#include <chrono>

#include <SDL2/SDL.h>
#include <glm/gtx/compatibility.hpp>

StatePlaying::StatePlaying(Application& app)
  : StateBase(app)
  , _cellRenderer(_mainCamera)
  , _fb(app.window.geometry().x, app.window.geometry().y)
  , _simulating(false)
{
    _cellWorld.init(worldXSize, worldYSize);
    _mainCamera.init(app.window.geometry().x, app.window.geometry().y);
    glm::vec2 worldSize = _cellWorld.worldSize();
    _grid.init(worldSize.x, worldSize.y);
    for (int x = 0; x < worldSize.x; x++)
    {
        for (int y = 0; y < worldSize.y; y++)
        {
            if ((rand() % 10) % 2 == 0)
                _cellWorld.put(x, y);
        }
    }
    _mainCamera.setScale(8.0f);
    _mainCamera.setPosition(glm::vec2(worldSize.x / 2, worldSize.y / 2));
    _quadShader =
      ResourceManager::getShader("./Shaders/quad.vert", "./Shaders/quad.frag");
}

void StatePlaying::input(float deltaTime)
{
    if (InputManager::isKeyPressed(SDLK_SPACE))
    {
        _simulating = !_simulating;
    }
    if (InputManager::isKeyPressed(SDLK_RIGHT) and !_simulating)
        _cellWorld.simStep();
    if (InputManager::isKeyPressed(SDLK_LEFT) and !_simulating)
        _cellWorld.pop();
    static glm::vec2 cameraPosition = _mainCamera.getPosition();
    static const float cameraSpeed = 50.0f;
    static const float zoomSpeed = 5.0f;

    if (InputManager::isKeyDown(SDL_BUTTON_RIGHT))
    {
        glm::vec2 target = _mainCamera.convertScreenToWorld(
          InputManager::getRelativeMouseCoord());
        _cellWorld.remove(target.x, target.y);
    }
    if (InputManager::isKeyDown(SDL_BUTTON_LEFT))
    {
        glm::vec2 target = _mainCamera.convertScreenToWorld(
          InputManager::getRelativeMouseCoord());
        _cellWorld.put(int(target.x), target.y);
    }

    if (InputManager::isKeyDown(SDLK_d))
        cameraPosition.x += cameraSpeed * deltaTime;
    if (InputManager::isKeyDown(SDLK_a))
        cameraPosition.x -= cameraSpeed * deltaTime;
    if (InputManager::isKeyDown(SDLK_w))
        cameraPosition.y += cameraSpeed * deltaTime;
    if (InputManager::isKeyDown(SDLK_s))
        cameraPosition.y -= cameraSpeed * deltaTime;

    if (InputManager::isKeyDown(SDLK_q))
        _mainCamera.addScale(zoomSpeed * deltaTime);
    if (InputManager::isKeyDown(SDLK_e))
        _mainCamera.addScale(-zoomSpeed * deltaTime);

    glm::vec2 worldSize = _cellWorld.worldSize();
    cameraPosition = glm::clamp(cameraPosition, glm::vec2(0.0f), worldSize);

    glm::vec2 vec =
      glm::lerp(_mainCamera.getPosition(), cameraPosition, 10.0f * deltaTime);
    _mainCamera.setPosition(vec);
}

void StatePlaying::update(float deltaTime)
{
    _mainCamera.update();
    if (_simulating)
        _cellWorld.simStep();
}

void StatePlaying::preDraw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void StatePlaying::draw()
{
    uint generation = _cellWorld.currentGeneration();
    auto board = _cellWorld.getBoard();
    _fb.bind();
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        for (auto it : board)
        {
            _cellRenderer.draw(it, generation);
        }
        _grid.draw(_mainCamera);
    }
    _fb.unBind();

    _quadShader.use();
    {
        glm::vec2 windowGeometry = _app->window.geometry();
        _quadShader.setUniform("screenResolution", windowGeometry);
        _quadShader.setTexture("fb", _fb.colorBuffer.ID);
        _quadShader.setUniform("onPause", _simulating);
        auto now = std::chrono::high_resolution_clock::now();
        auto nanos = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
        _quadShader.setUniform("time", (float)(nanos%1000000));
        glDisable(GL_DEPTH_TEST);
        _simpleRenderer.quad();
        glEnable(GL_DEPTH_TEST);
    }
}

void StatePlaying::postDraw()
{
    _app->window.swapBuffer();
    SDL_Delay(1);
}
