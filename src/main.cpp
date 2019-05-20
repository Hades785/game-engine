// OpenGL
#include <GL/glew.h>
// OpenGL Math
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// SFML
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>

#include "Game.h"
#include "GameEngine/Assets/ResourceManager.h"


// Window width and height
#define WIDTH 600
#define HEIGHT 400

// OpenGL context settings
#define BIT_DEPTH 24
#define BIT_STENCIL 8
#define ANTIALIAS_LVL 4
#define MAJOR_VERSION 3 // OpenGL v3.X
#define MINOR_VERSION 3 // OpenGL vX.3

Game game(WIDTH, HEIGHT);

void handleKeyPressed(sf::Keyboard::Key key);

void handleKeyReleased(sf::Keyboard::Key key);

int main() {
    sf::ContextSettings settings;
    settings.depthBits = BIT_DEPTH;
    settings.stencilBits = BIT_STENCIL;
    settings.antialiasingLevel = ANTIALIAS_LVL;
    settings.majorVersion = MAJOR_VERSION;
    settings.minorVersion = MINOR_VERSION;
    settings.attributeFlags = sf::ContextSettings::Core;

    // Window creation
    sf::Window window(sf::VideoMode(WIDTH, HEIGHT),
                      "Sprite Testing",
                      sf::Style::Default, settings);

    glewExperimental = GL_TRUE;
    glewInit();
    glGetError();

    glEnable(GL_TEXTURE_2D);

    glViewport(0, 0, WIDTH, HEIGHT);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    game.init();

    // Clock for time delta
    sf::Clock clock;

    game.state = GAME_MENU;

    // Main loop
    bool running = true;
    while (running) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    running = false;
                    break;
                case sf::Event::Resized:
                    glViewport(0, 0, event.size.width, event.size.height);
                    game.width = event.size.width;
                    game.height = event.size.height;
                    break;
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Escape)
                        running = false;
                    else
                        handleKeyPressed(event.key.code);
                    break;
                case sf::Event::KeyReleased:
                    handleKeyReleased(event.key.code);
                    break;
            }
        }

        sf::Time timeDelta = clock.restart();
        game.processInput(timeDelta);
        game.update(timeDelta);

        glClearColor(50 / 255.f, 150 / 255.f, 250 / 255.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);
        game.render();

        window.display();
    }

    // Freeing OpenGL assets
    ResourceManager::clear();

    window.close();
    return 0;
}

void handleKeyPressed(sf::Keyboard::Key key) {
    game.keys[key] = GL_TRUE;
}

void handleKeyReleased(sf::Keyboard::Key key) {
    game.keys[key] = GL_FALSE;
}
