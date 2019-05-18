//
// Created by fuzuki on 05/04/19.
//

#ifndef GAME_H
#define GAME_H

#include <GL/glew.h>
#include <SFML/System.hpp>

enum GameState {
    GAME_MENU,
    GAME_ACTIVE,
    GAME_WIN,
    GAME_OVER
};


class Game {
public:
    GameState state;
    GLboolean keys[1024];
    GLuint width, height;

    Game(GLuint width, GLuint height);
    ~Game();

    void init();

    void processInput(sf::Time dt);
    void update(sf::Time dt);
    void render();
};


#endif //GAME_H
