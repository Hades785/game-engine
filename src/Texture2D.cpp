//
// Created by fuzuki on 11/04/19.
//

#include "Texture2D.h"

Texture2D::Texture2D()
        : width(0), height(0),
          textureFormat(GL_RGB), imageFormat(GL_RGB),
          wrapS(GL_REPEAT), wrapT(GL_REPEAT),
          filterMin(GL_LINEAR), filterMax(GL_LINEAR) {
    glGenTextures(1, &this->ID);
}

void Texture2D::generate(sf::Image& image) {
    this->width = image.getSize().x;
    this->height = image.getSize().y;

    // bind
    glBindTexture(GL_TEXTURE_2D, this->ID);

    // load image data
    glTexImage2D(GL_TEXTURE_2D, 0, this->textureFormat,
                 image.getSize().x, image.getSize().y, 0,
                 this->imageFormat, GL_UNSIGNED_BYTE, image.getPixelsPtr());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->wrapT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->filterMin);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->filterMax);

    // unbind
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::bind() const {
    glBindTexture(GL_TEXTURE_2D, this->ID);
}
