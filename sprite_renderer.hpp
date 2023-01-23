#pragma once

#include "shader.hpp"
#include "texture.hpp"

class SpriteRenderer
{
    public:
        SpriteRenderer(Shader &shader, int number_of_columns = 1, int number_of_rows = 1);
        ~SpriteRenderer();

        void DrawSprite(Texture2D &texture, glm::vec2 position, 
            glm::vec2 size = glm::vec2(10.0f, 10.0f), float rotate = 0.0f, 
            glm::vec3 color = glm::vec3(1.0f), int frame = 0);
    private:
        Shader       shader; 
        unsigned int quadVAO;

        void initRenderData(int number_of_columns, int number_of_rows);
};