//
// Created by fuzuki on 11/04/19.
//

#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include <GL/glew.h>
#include <SFML/Graphics.hpp>

class Texture2D {
public:
    GLuint ID;
    GLuint width, height;

    GLuint textureFormat;
    GLuint imageFormat;

    GLuint wrapS;
    GLuint wrapT;
    GLuint filterMin;
    GLuint filterMax;

    Texture2D();

    void generate(sf::Image& image);

    void bind() const;
};


#endif //TEXTURE2D_H
