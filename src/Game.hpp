#ifndef __GAME_H__
#define __GAME_H__

#include "Camera.hpp"
#include "CubeRenderer.hpp"
#include "Window.hpp"

class Game {
private:
    const Uint8* m_keyState; // to handle keyboard events
    float m_deltaTime = 0;

    ShaderProgram m_shaderProgram;

    int m_windowWidth = 1000;
    int m_windowHeight = 800;

    Window* m_myWindow           = nullptr;
    CubeRenderer* m_cubeRenderer = nullptr;

    Camera m_camera;

    bool m_isRunning;

    void preRender();
public:
    Game();
    ~Game();

    void handleEvents();
    void update();
    void renderAll();
    bool isRuning();
};

#endif // __GAME_H__