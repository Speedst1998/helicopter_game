#include <fmt/core.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "sprite_renderer.hpp"

SpriteRenderer::SpriteRenderer(Shader &shader, int number_of_columns, int number_of_rows)
{
    this->shader = shader;
    this->initRenderData(number_of_columns, number_of_rows);
}

SpriteRenderer::~SpriteRenderer()
{
    glDeleteVertexArrays(1, &this->quadVAO);
}

void SpriteRenderer::initRenderData(int number_of_columns, int number_of_rows) {
    unsigned int VBO;
    float vertices[] = {
        // Pos      // Tex
        0.0f, 1.0f, 0.0f, 1.0f/number_of_rows,
        1.0f, 0.0f, 1.0f/number_of_columns, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 1.0f/number_of_rows,
        1.0f, 1.0f, 1.0f/number_of_columns, 1.0f/number_of_rows,
        1.0f, 0.0f, 1.0f/number_of_columns, 0.0f
    };
    glGenVertexArrays(1, &this->quadVAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindVertexArray(this->quadVAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void SpriteRenderer::DrawSprite(Texture2D &texture, glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 color, int frameIndex)
{
    this->shader.Use();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));
    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
    model = glm::rotate(model, rotate, glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));
    model = glm::scale(model, glm::vec3(size, 1.0f));
    this->shader.SetMatrix4("model", model);
    this->shader.SetVector3f("spriteColor", color);
    this->shader.SetInteger("frameIndex", frameIndex);
    glActiveTexture(GL_TEXTURE0);
    texture.Bind();
    glBindVertexArray(this->quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}