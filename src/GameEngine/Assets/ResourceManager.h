//
// Created by fuzuki on 12/04/19.
//

#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <map>
#include <string>

#include <GL/glew.h>

#include "GameEngine/Assets/Shaders/Shader.h"
#include "GameEngine/Assets/Sprites/Texture2D.h"

class ResourceManager {
public:
    // resource storage
    static std::map<std::string, Shader> shaders;
    static std::map<std::string, Texture2D> textures;

    static Shader loadShader(std::string name,
                             const GLchar* vShaderFile,
                             const GLchar* fShaderFile,
                             const GLchar* gShaderFile = nullptr);

    static Shader getShader(std::string name);

    static Texture2D loadTexture(std::string name,
                                 const GLchar* file,
                                 GLboolean alpha);

    static Texture2D getTexture(std::string name);

    // free assets
    static void clear();

private:
    ResourceManager() {}

    static Shader loadShaderFromFile(const GLchar* vShaderFile,
                                     const GLchar* fShaderFile,
                                     const GLchar* gShaderFile);

    static Texture2D loadTextureFromFile(const GLchar* file, GLboolean alpha);
};


#endif //RESOURCEMANAGER_H
