//
// Created by fuzuki on 18/05/19.
//

#ifndef TILESET_H
#define TILESET_H


#include "../Sprites/Texture2D.h"

class TileSet {
private:
    GLint sheetWidth, sheetHeight;
    Texture2D sheet;

    GLint tileWidth, tileHeight;

public:
    /**
     * Load tileset from tileset definition file
     * @param file tileset definition file
     * @param tilesetName tileset to load
     */
    TileSet(GLchar* file, GLchar* tilesetName);
};


#endif //TILESET_H
