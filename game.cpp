#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "game.hpp"
#include "resource_manager.hpp"
#include "sprite_renderer.hpp"
#include "game_level.hpp"
#include "shader.hpp"


SpriteRenderer  *Renderer;
Game::Game(unsigned int width, unsigned int height)
    : State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{
}

Game::~Game()
{
    delete Renderer;
    Renderer = nullptr;
}

void Game::Init(){
    // load shaders
    ResourceManager::LoadShader("shaders/sprite.vs", "shaders/sprite.frag", nullptr, "sprite");
    // configure shaders
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width), static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
    auto shader = ResourceManager::GetShader("sprite");
    Renderer = new SpriteRenderer(shader);
    auto player_texture = ResourceManager::LoadTexture("textures/helicopter.png", true, "helicopter");
    ResourceManager::LoadTexture("textures/2.png", true, "grass");
    PlayerObject = std::make_unique<Player>(glm::vec2(20,20), glm::vec2(90, 90), player_texture);
    GameLevel one; one.Load("levels/one.lvl", this->Width, this->Height);
    Levels.push_back(one);

    Level = 0;

}
    
    
    
void Game::Render(){
    // Texture2D texture = ResourceManager::GetTexture("helicopter"); 
    // Renderer->DrawSprite(texture, glm::vec2(20.0f, 20.0f), glm::vec2(90, 90), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    PlayerObject->Draw(*Renderer);
    Levels[Level].Draw(*Renderer);
}

void Game::Update(float dt) {
    
}

void Game::ProcessInput(float delta_time) {
    PlayerObject->ProcessInput(Keys, delta_time);
}