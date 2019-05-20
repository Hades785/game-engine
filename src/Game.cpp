//
// Created by fuzuki on 05/04/19.
//

#include "Game.h"
#include "GameEngine/Assets/ResourceManager.h"
#include "GameEngine/Assets/Sprites/SpriteRenderer.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

SpriteRenderer* renderer;

Game::Game(GLuint width, GLuint height)
        : state(GAME_MENU), keys(), width(width), height(height) {
}

Game::~Game() {
}

void Game::init() {
    ResourceManager::loadShader("sprite",
                                "../assets/shaders/vertexShader.glsl",
                                "../assets/shaders/fragmentShader.glsl");

    // (0;0) top left | (width;height) bottom right
    glm::mat4 projection = glm::ortho(0.f, static_cast<GLfloat>(this->width),
                                      static_cast<GLfloat>(this->height), 0.f,
                                      -1.f, 1.f);

    // (0;0) bottom left | (width;height) top right
    //glm::mat4 projection = glm::ortho(0.f, static_cast<GLfloat>(this->width),
    //                                  0.f, static_cast<GLfloat>(this->height),
    //                                  -1.f, 1.f);

    Shader shader = ResourceManager::getShader("sprite");
    shader.setInteger("image", 0, GL_TRUE);
    shader.setMatrix4("projection", projection);

    renderer = new SpriteRenderer(shader);

    ResourceManager::loadTexture("tex1", "../assets/img.png", GL_TRUE);
}

void Game::processInput(sf::Time dt) {
}

void Game::update(sf::Time dt) {
}

void Game::render() {
    static int i = 0;
    const double pi = 3.14159265358979323846;

    Texture2D tex1 = ResourceManager::getTexture("tex1");
    renderer->drawSprite(tex1, glm::vec2(100, 100), glm::vec2(200, 200),
                         0.f, glm::vec3(1.f, 1.f, 1.f));
    renderer->drawSprite(tex1, glm::vec2(i, 100), glm::vec2(200, 200),
                         -pi / 4, glm::vec3(1.f, 0.f, 0.f));

    i = i + 0 == width ? -200 : i + 1;
}
