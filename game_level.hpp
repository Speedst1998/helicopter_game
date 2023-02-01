#pragma once

#include <glad/glad.h>
#include <vector>
#include "sprite_renderer.hpp"
#include "game_object.hpp"

class GameLevel
{
public:
    // GameLevel state
    std::vector<GameObject> Bricks;
    // Constructor
    GameLevel();
    // Loads level from file
    void Load(const GLchar *file, GLuint levelWidth, GLuint levelHeight);
    // Render level
    void Draw(SpriteRenderer &renderer);
    // Check if the level is completed (all non-solid tiles are destroyed)
    GLboolean IsCompleted();

private:
    int CurrentEdge = 0;
    void Init(std::vector<std::vector<GLuint>> tileData, GLuint levelWidth, GLuint levelHeight);
};