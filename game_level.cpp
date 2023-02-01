#include <fstream>
#include <sstream>
#include <iostream>
#include "game_level.hpp"
#include "resource_manager.hpp"

GameLevel::GameLevel()
{
}

void GameLevel::Init(std::vector<std::vector<unsigned int>> tileData, unsigned int levelWidth, unsigned int levelHeight)
{
    // Calculate dimensions
    unsigned int height = tileData.size();
    unsigned int width = tileData[0].size(); // Note we can index vector at [0] since this function is only called if height > 0
    GLfloat unit_width = levelWidth / static_cast<GLfloat>(width), unit_height = levelHeight / height;
    // Initialize level tiles based on tileData		
    for (unsigned int y = 0; y < height; ++y)
    {
        for (unsigned int x = 0; x < width; ++x)
        {
            // Check block type from level data (2D level array)
            glm::vec2 pos(unit_width * x, unit_height * y);
            glm::vec2 size(unit_width, unit_height);
            switch(tileData[y][x]) // Solid
            {
                case 1:
                {
                    GameObject obj(pos, size, ResourceManager::GetTexture("grass"), glm::vec3(0.8f, 0.8f, 0.7f));
                    obj.IsSolid = true;
                    this->Bricks.push_back(obj);
                    break;
                }
                case 2:
                {
                    this->Bricks.push_back(GameObject(pos, size, ResourceManager::GetTexture("sky"), glm::vec3(1.0f, 1.0f, 1.0f)));
                    break;
                }
                case 3:
                {
                    this->Bricks.push_back(GameObject(pos, size, ResourceManager::GetTexture("cloud"), glm::vec3(1.0f, 1.0f, 1.0f)));
                    break;
                }
                default:
                {
                    this->Bricks.push_back(GameObject(pos, size, ResourceManager::GetTexture("sky"), glm::vec3(0.0f, 0.0f, 0.0f)));
                    break;
                }
            }
        }
    }
}

void GameLevel::Load(const GLchar *file, unsigned int levelWidth, unsigned int levelHeight)
{
    // Clear old data
    this->Bricks.clear();
    // Load from file
    unsigned int tileCode;
    GameLevel level;
    std::string line;
    std::ifstream in_file(file);
    std::vector<std::vector<unsigned int>> tileData;
    if (in_file)
    {
        while (std::getline(in_file, line)) // Read each line from level file
        {
            std::istringstream sstream(line);
            std::vector<unsigned int> row;
            while (sstream >> tileCode) // Read each word seperated by spaces
                row.push_back(tileCode);
            tileData.push_back(row);
        }
        if (tileData.size() > 0)
            this->Init(tileData, levelWidth, levelHeight);
    }
}

void GameLevel::Draw(SpriteRenderer &renderer)
{
    static int counter = 0;
    CurrentEdge = (CurrentEdge + 1 ) % 800; 
    for (GameObject &tile : this->Bricks)
        if (!tile.Destroyed)
            tile.Draw(renderer);
}