#include "player.hpp"

#include "GLFW/glfw3.h"
Player::Player(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color, glm::vec2 velocity) : GameObject(pos, size, sprite, color, velocity)
{
}

void Player::ProcessInput(const bool keys[], float delta_time)
{
    float velocity = PLAYER_VELOCITY * delta_time;
    // move playerboard
    if (keys[GLFW_KEY_A])
    {
        Position.x -= velocity;
    }
    if (keys[GLFW_KEY_D])
    {
        Position.x += velocity;
    }
    if (keys[GLFW_KEY_W])
    {
        Position.y -= velocity;
    }
    if (keys[GLFW_KEY_S])
    {
        Position.y += velocity;
    }
}