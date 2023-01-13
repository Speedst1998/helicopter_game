#include "game_object.hpp"

class Player : public GameObject {
    private:
        const float PLAYER_VELOCITY = 100;
    public:
        Player(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));
        void ProcessInput(const bool keys[], float delta_time);
};