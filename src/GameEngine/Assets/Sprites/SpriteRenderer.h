//
// Created by fuzuki on 13/04/19.
//

#ifndef SPRITERENDERER_H
#define SPRITERENDERER_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.h"
#include "GameEngine/Assets/Sprites/Texture2D.h"

class SpriteRenderer {
public:
    SpriteRenderer(Shader& shader);

    ~SpriteRenderer();

    void drawSprite(Texture2D& texture,
                    glm::vec2 position,
                    glm::vec2 size = glm::vec2(10, 10),
                    GLfloat rotate = 0.f,
                    glm::vec3 color = glm::vec3(1.f));

private:
    Shader shader;
    GLuint quadVAO;

    void initRenderData();
};


#endif //SPRITERENDERER_H
