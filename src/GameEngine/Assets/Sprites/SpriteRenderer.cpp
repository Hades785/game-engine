//
// Created by fuzuki on 13/04/19.
//

#include "SpriteRenderer.h"


SpriteRenderer::SpriteRenderer(Shader& shader) {
    this->shader = shader;
    this->initRenderData();
}

SpriteRenderer::~SpriteRenderer() {
    glDeleteVertexArrays(1, &this->quadVAO);
}

void SpriteRenderer::drawSprite(Texture2D& texture,
                                glm::vec2 position, glm::vec2 size,
                                GLfloat rotate, glm::vec3 color) {
    this->shader.use();

    glm::mat4 model = glm::mat4(1.0);
    model = glm::translate(model, glm::vec3(position, 0.f));
    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.f));
    model = glm::rotate(model, rotate, glm::vec3(0.f, 0.f, 1.f));
    model = glm::translate(model, glm::vec3(-.5f * size.x, -.5f * size.y, 0.f));
    model = glm::scale(model, glm::vec3(size, 1.f));

    this->shader.setMatrix4("model", model);
    this->shader.setVector3f("spriteColor", color);

    glActiveTexture(GL_TEXTURE0);
    texture.bind();

    glBindVertexArray(this->quadVAO);

    glDrawElements(GL_TRIANGLES, (3 * 2), GL_UNSIGNED_INT, (void*) 0);
    //glDrawArrays(GL_TRIANGLES, (3 * 2), 0);
    glBindVertexArray(0);
}


void SpriteRenderer::initRenderData() {
    GLuint vbo, ebo;

    //      x     y     tx    ty
    GLfloat vertices[] = {
            0.0f, 0.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 1.0f, 0.0f,
            1.0f, 1.0f, 1.0f, 1.0f,
            0.0f, 1.0f, 0.0f, 1.0f
    };

    GLuint elements[] = {
            3, 1, 0,
            3, 2, 1
    };

    glGenVertexArrays(1, &this->quadVAO);
    glBindVertexArray(this->quadVAO);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(vertices), vertices,
                 GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 sizeof(elements), elements,
                 GL_STATIC_DRAW);

    GLuint vAttrib = glGetAttribLocation(shader.ID, "vertex");
    glEnableVertexAttribArray(vAttrib);
    glVertexAttribPointer(vAttrib, 4, GL_FLOAT, GL_FALSE,
                          4 * sizeof(GLfloat), (GLvoid*) 0);

    // Unbind buffers
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
