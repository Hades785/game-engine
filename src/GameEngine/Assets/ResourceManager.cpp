//
// Created by fuzuki on 12/04/19.
//

#include "ResourceManager.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include <SFML/Graphics.hpp>

std::map<std::string, Shader> ResourceManager::shaders;
std::map<std::string, Texture2D> ResourceManager::textures;

Shader ResourceManager::loadShader(std::string name,
                                   const GLchar* vShaderFile,
                                   const GLchar* fShaderFile,
                                   const GLchar* gShaderFile) {
    shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
    return shaders[name];
}

Shader ResourceManager::getShader(std::string name) {
    return shaders[name];
}

Texture2D ResourceManager::loadTexture(std::string name,
                                       const GLchar* file,
                                       GLboolean alpha) {
    textures[name] = loadTextureFromFile(file, alpha);
    return textures[name];
}

Texture2D ResourceManager::getTexture(std::string name) {
    return textures[name];
}

void ResourceManager::clear() {
    for (auto iter : shaders)
        glDeleteProgram(iter.second.ID);
    for (auto iter : textures)
        glDeleteTextures(1, &iter.second.ID);
}

Shader ResourceManager::loadShaderFromFile(const GLchar* vShaderFile,
                                           const GLchar* fShaderFile,
                                           const GLchar* gShaderFile) {
    std::string vertexCode;
    std::string fragmentCode;
    std::string geometryCode;

    try {
        // Open files
        std::ifstream vertexShaderFile(vShaderFile);
        std::ifstream fragmentShaderFile(fShaderFile);

        // Read files
        std::stringstream vShaderStream, fShaderStream;
        vShaderStream << vertexShaderFile.rdbuf();
        fShaderStream << fragmentShaderFile.rdbuf();

        // Close files
        vertexShaderFile.close();
        fragmentShaderFile.close();

        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();

        // Load geometryShader if path given
        if (gShaderFile != nullptr) {
            std::ifstream geometryShaderFile(gShaderFile);

            std::stringstream gShaderStream;
            gShaderStream << geometryShaderFile.rdbuf();

            geometryShaderFile.close();

            geometryCode = gShaderStream.str();
        }
    } catch (std::exception& e) {
        std::cerr << "ERROR::RESOURCE: failed to read shader files"
                  << std::endl;
    }

    const GLchar* vShaderCode = vertexCode.c_str();
    const GLchar* fShaderCode = fragmentCode.c_str();
    const GLchar* gShaderCode = gShaderFile != nullptr
                                               ? geometryCode.c_str()
                                               : nullptr;

    Shader shader;
    shader.compile(vShaderCode, fShaderCode, gShaderCode);
    return shader;
}

Texture2D ResourceManager::loadTextureFromFile(const GLchar* file,
                                               GLboolean alpha) {
    Texture2D texture;

    if (alpha) {
        texture.textureFormat = GL_RGBA;
        texture.imageFormat = GL_RGBA;
    } else {
        texture.textureFormat = GL_RGB;
        texture.imageFormat = GL_RGB;
    }
    texture.wrapS = GL_CLAMP_TO_EDGE;
    texture.wrapT = GL_CLAMP_TO_EDGE;
    texture.filterMin = GL_LINEAR;
    texture.filterMax = GL_LINEAR;

    sf::Image image;
    image.loadFromFile(file);

    texture.generate(image);
    return texture;
}
