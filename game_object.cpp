#include "game_object.hpp"
#include "texture.hpp"
#include "sprite_renderer.hpp"

GameObject::GameObject()
    : Position(0.0f, 0.0f), Size(1.0f, 1.0f), Velocity(0.0f), Color(1.0f), Rotation(0.0f), Sprite(), IsSolid(false), Destroyed(false){};
GameObject::GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color, glm::vec2 velocity) : Position(pos), Size(size), Velocity(velocity), Color(color), Rotation(0.0f), Sprite(sprite), IsSolid(false), Destroyed(false){};

void GameObject::Draw(SpriteRenderer &renderer)
{
    renderer.DrawSprite(this->Sprite, this->Position, this->Size, this->Rotation, this->Color);
}

void GameObject::SetGameObject(const GameObject&& game_object) {
    Position = std::move(game_object.Position);
    Size = std::move(game_object.Size);
    Velocity = std::move(game_object.Velocity);
    Color = std::move(game_object.Color);
    Rotation = std::move(game_object.Rotation);
    Sprite = std::move(game_object.Sprite);
    IsSolid = std::move(game_object.IsSolid);
    Destroyed = std::move(game_object.Destroyed);
}

void GameObject::SetGameObject(const GameObject& game_object) {
    Position = game_object.Position;
    Size = game_object.Size;
    Velocity = game_object.Velocity;
    Color = game_object.Color;
    Rotation = game_object.Rotation;
    Sprite = game_object.Sprite;
    IsSolid = game_object.IsSolid;
    Destroyed =game_object.Destroyed;
}