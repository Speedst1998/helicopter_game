#include "shader.hpp"
#include "texture.hpp"

#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <sstream>

class ResourceManager {
public:
    static std::map<std::string,Shader> shaders;
    static std::map<std::string,Texture2D> textures;

    static Shader LoadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, std::string name);
    static Shader GetShader(std::string name);
    static Texture2D LoadTexture(const char* file, bool alpha, std::string name);
    static Texture2D GetTexture(std::string name);
    static void Clear();

    private:
    ResourceManager() { }
    static Shader loadShaderFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile = nullptr);
    static Texture2D loadTextureFromFile(const char* file, bool alpha);

};