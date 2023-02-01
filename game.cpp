#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <fmt/core.h>

#include "game.hpp"
#include "resource_manager.hpp"
#include "sprite_renderer.hpp"
#include "game_level.hpp"
#include "shader.hpp"

SpriteRenderer *PlayerRenderer;
SpriteRenderer *TileRenderer;
Game::Game(unsigned int width, unsigned int height)
    : State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{
}

Game::~Game()
{
    delete PlayerRenderer;
    PlayerRenderer = nullptr;
}

void Game::Init()
{
    // load shaders
    ResourceManager::LoadShader("shaders/player_sprite.vs", "shaders/sprite.frag", nullptr, "player_sprite");
    ResourceManager::LoadShader("shaders/tile_sprite.vs", "shaders/sprite.frag", nullptr, "tile_sprite");
    // configure shaders
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width), static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("player_sprite").Use().SetInteger("image", 0);
    ResourceManager::GetShader("player_sprite").SetMatrix4("projection", projection);
    ResourceManager::GetShader("tile_sprite").Use().SetInteger("image", 0);
    ResourceManager::GetShader("tile_sprite").SetMatrix4("projection", projection);
    camera_view = glm::lookAt(glm::vec3(0.0f, 0.0f, 1.0f),
                       glm::vec3(0.0f, 0.0f, 0.0f),
                       glm::vec3(0.0f, 1.0f, 0.0f));
    ResourceManager::GetShader("tile_sprite").SetMatrix4("view", camera_view);
    auto shader = ResourceManager::GetShader("player_sprite");
    PlayerRenderer = new SpriteRenderer(shader, 8);
    auto tile_shader = ResourceManager::GetShader("tile_sprite");
    TileRenderer = new SpriteRenderer(tile_shader);
    auto player_texture = ResourceManager::LoadTexture("textures/helicopter_anim/helicopter.png", true, "helicopter");
    ResourceManager::LoadTexture("textures/2.png", true, "grass");
    ResourceManager::LoadTexture("textures/18.png", true, "sky");
    ResourceManager::LoadTexture("textures/clouds/PNG/Clouds_white/Shape3/cloud_shape3_3.png", true, "cloud");
    ResourceManager::LoadTexture("textures/sky_background/Clouds/Clouds 4/1.png", true, "background1");
    BackgroundObject = std::make_unique<GameObject>(glm::vec2(0, 0), glm::vec2(Width, Height), ResourceManager::GetTexture("background1"), glm::vec3(1), glm::vec2(0, 0));
    PlayerObject = std::make_unique<Player>(glm::vec2(20, 20), glm::vec2(90, 90), player_texture, glm::vec3(1), glm::vec2(100, 100));
    GameLevel one;
    one.Load("levels/one.lvl", this->Width, this->Height);
    Levels.push_back(one);

    Level = 0;
}

void Game::Render(float delta_time)
{
    // Texture2D texture = ResourceManager::GetTexture("helicopter");
    // Renderer->DrawSprite(texture, glm::vec2(20.0f, 20.0f), glm::vec2(90, 90), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    static float x = 0;
    fmt::print("x -> {} \n", x);
    camera_view = glm::lookAt(glm::vec3(x++, 0.0f, 1.0f),
                       glm::vec3(0.0f, 0.0f, 0.0f),
                       glm::vec3(0.0f, 1.0f, 0.0f));
    ResourceManager::GetShader("tile_sprite").SetMatrix4("view", camera_view);
    BackgroundObject->Draw(*TileRenderer);
    Levels[Level].Draw(*TileRenderer);
    PlayerObject->Draw(*PlayerRenderer);
}

void Game::Update(float dt)
{
    DoCollisions();
}

void Game::ProcessInput(float delta_time)
{
    PlayerObject->ProcessInput(Keys, delta_time);
}

bool CheckCollision(const GameObject &game_object1, const GameObject &game_object2);

void Game::DoCollisions()
{
    for (const auto &tile : Levels[Level].Bricks)
    {
        if (CheckCollision(*PlayerObject, tile))
        {
            if (tile.IsSolid)
            {
                // fmt::print("Collision Detected.  Player : x -> {} x + size  {}, Tile : {} \n", PlayerObject->Position.x, PlayerObject->Position.x + PlayerObject->Size.x, tile.Position.x);
                PlayerObject->Velocity = glm::vec2(0);
                PlayerObject->ReboundFlag = true;
            }
        }
    }
}

bool CheckCollision(const GameObject &game_object1, const GameObject &game_object2)
{
    auto is_collided_y = ((game_object1.Position.y + game_object1.Size.y) >= game_object2.Position.y) && (game_object2.Position.y <= (game_object1.Position.y + game_object1.Size.y));
    auto is_collided_x = ((game_object1.Position.x + game_object1.Size.x) >= game_object2.Position.x) && (game_object2.Position.x + game_object2.Size.x >= (game_object1.Position.x));
    // fmt::print("gm1 X : {} , gm1 Y : {}, gm2 X : {} , gm2 Y {}\n", game_object1.Position.x, game_object1.Position.y, game_object2.Position.x, game_object2.Position.y);
    return is_collided_x && is_collided_y;
}