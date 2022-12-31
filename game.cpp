#include "game.hpp"
#include "resource_manager.hpp"
#include "sprite_renderer.hpp"
#include "game_level.hpp"


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
    ResourceManager::LoadShader("../shaders/sprite.vs", "../shaders/sprite.frag", nullptr, "sprite");
    // configure shaders
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width), static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);

    Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
    ResourceManager::LoadTexture("../textures/awesomeface.png", true, "helicopter");
    ResourceManager::LoadTexture("../textures/2.png", true, "grass");

    GameLevel one; one.Load("../levels/one.lvl", this->Width, this->Height * 0.5);
    Levels.push_back(one);

    Level = 0;

}
    
    
    
void Game::Render(){
    Texture2D texture = ResourceManager::GetTexture("helicopter"); 
    //Renderer->DrawSprite(texture, glm::vec2(200.0f, 200.0f), glm::vec2(300.0f, 400.0f), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    Levels[Level].Draw(*Renderer);
}