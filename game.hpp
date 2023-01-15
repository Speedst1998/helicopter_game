#include <memory>

#include "sprite_renderer.hpp"
#include "game_level.hpp"
#include "player.hpp"

enum GameState
{
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

class Game
{
public:
    // game state
    GameState State;
    bool Keys[1024];
    unsigned int Width, Height;
    std::vector<GameLevel> Levels;
    unsigned int Level;
    std::unique_ptr<Player> PlayerObject = nullptr;
    // constructor/destructor
    Game(unsigned int width, unsigned int height);
    ~Game();
    // initialize game state (load all shaders/textures/levels)
    void Init();
    // game loop
    void ProcessInput(float dt);
    void Update(float dt);
    void Render();
    void SetPlayer(const GameObject&& player);
    void DoCollisions();
};