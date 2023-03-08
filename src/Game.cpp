#include "Game.hpp"

void initializeGlad() {
    if (!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
        throw std::runtime_error("Failed to initialize GLAD");
    }

    std::cout << "VENDOR: " << glGetString(GL_VENDOR) << '\n';
    std::cout << "RENDERER: " << glGetString(GL_RENDERER) << '\n';
    std::cout << "VERSION: " << glGetString(GL_VERSION) << '\n';
    std::cout << "GLSL VERSION:" << glGetString(GL_SHADING_LANGUAGE_VERSION) << '\n';
}

Game::Game() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) throw std::runtime_error("Cannot intialize SDL\n");
    m_myWindow = new Window(m_windowWidth, m_windowHeight, "Minecraft Clone");
    m_myWindow->createWindow();
    m_myWindow->createGLContext();

    initializeGlad();

    m_shaderProgram.loadSource("resources/fragment.frag", ShaderProgram::FRAGMENT);
    m_shaderProgram.loadSource("resources/vertex.vert", ShaderProgram::VERTEX);
    m_shaderProgram.createShaderProgram();

    m_keyState = SDL_GetKeyboardState(nullptr);

    SDL_SetRelativeMouseMode(SDL_TRUE);

    GLCall(glViewport(0, 0, m_windowWidth, m_windowHeight));
    GLCall(glEnable(GL_DEPTH_TEST));

    m_cubeRenderer = new CubeRenderer(m_shaderProgram);

    m_isRunning = true;
}

Game::~Game() {
    if (m_myWindow != nullptr) delete m_myWindow;
    if (m_cubeRenderer != nullptr) delete m_cubeRenderer;
    SDL_Quit();
}

void Game::handleEvents() {
    int xpos, ypos;
    SDL_GetRelativeMouseState(&xpos, &ypos);

    if (m_keyState[SDL_SCANCODE_W] == 1) m_camera.translate(Camera::Direction::FRONT, m_deltaTime);
    if (m_keyState[SDL_SCANCODE_S] == 1) m_camera.translate(Camera::Direction::BACK, m_deltaTime);
    if (m_keyState[SDL_SCANCODE_A] == 1) m_camera.translate(Camera::Direction::LEFT, m_deltaTime);
    if (m_keyState[SDL_SCANCODE_D] == 1) m_camera.translate(Camera::Direction::RIGTH, m_deltaTime);
    if (m_keyState[SDL_SCANCODE_LSHIFT] == 1) m_camera.translate(Camera::Direction::DOWN, m_deltaTime);
    if (m_keyState[SDL_SCANCODE_SPACE] == 1) m_camera.translate(Camera::Direction::UP, m_deltaTime);
    if (m_keyState[SDL_SCANCODE_LCTRL] == 1) {
        m_camera.setMovementSpeed(10.0f);
    } else {
        m_camera.setMovementSpeed(INITIAL_SPEED);
    }

    m_camera.processMouseOffsets(xpos, -ypos);

    // if (keyState[SDL_SCANCODE_UP] == 1) camera.processMouseOffsets(0, 10);
    // if (keyState[SDL_SCANCODE_RIGHT] == 1) camera.processMouseOffsets(10, 0);
    // if (keyState[SDL_SCANCODE_LEFT] == 1) camera.processMouseOffsets(-10, 0);
    // if (keyState[SDL_SCANCODE_DOWN] == 1) camera.processMouseOffsets(0, -10);

    if (m_keyState[SDL_SCANCODE_R] == 1) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    if (m_keyState[SDL_SCANCODE_E] == 1) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) m_isRunning = false;
        if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                m_isRunning = false;
            }
        }
    }
}

void Game::update() {
    static float lastFrame    = 0.0f;
    static float currentFrame = SDL_GetTicks64();

    currentFrame = SDL_GetTicks64();
    m_deltaTime  = (currentFrame - lastFrame) / 1000;
    lastFrame    = currentFrame;
}

void Game::renderAll() {
    glm::mat projection = glm::mat4 { 1.0f };
    projection          = glm::perspective(glm::radians(80.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    glm::vec3 cubePositions[] = { glm::vec3(0.0f, 0.0f, 0.0f),
                                  glm::vec3(1, 0, 0),
                                  glm::vec3(0, 0, 1),
                                  glm::vec3(0, 0, -1),
                                  glm::vec3(2.4f, -0.4f, -3.5f),
                                  glm::vec3(-1.7f, 3.0f, -7.5f),
                                  glm::vec3(1.3f, -2.0f, -2.5f),
                                  glm::vec3(1.5f, 2.0f, -2.5f),
                                  glm::vec3(1.5f, 0.2f, -1.5f),
                                  glm::vec3(-1.3f, 1.0f, -1.5f) };

    m_shaderProgram.useProgram();
    m_shaderProgram.setInt("texture1", 0);
    m_shaderProgram.setFloat("si", 0.5f);
    m_shaderProgram.setMat4("view", m_camera.getViewMatrix());
    m_shaderProgram.setMat4("projection", projection);

    // Handles the rendering
    preRender();
    for (int i = 0; i < 10; i++) {
        m_cubeRenderer->render(cubePositions[i], CubeRenderer::CubeType::STONE, ALL_FACES);
    }

    m_myWindow->SwapWindow();
}

bool Game::isRuning() { return m_isRunning; }

void Game::preRender() {
    GLCall(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
    // GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
    GLCall(glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT));
}
