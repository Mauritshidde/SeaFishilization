#include <map>
#include <string>
#include "../raylib.h"

class Tile 
{
private: 
    int tileSize;
    std::string type;
    std::map<std::string, Texture2D> textures;
    Vector2 pos;

public:
    Vector2 getPos();
    std::string getType();
    void changeType(std::string newType);
    void draw();
    Tile(int x, int y, double size, std::map<std::string, Texture2D>& tileTextures, std::string type_);
    ~Tile();
};

Tile::Tile(int x, int y, double size, std::map<std::string, Texture2D>& tileTextures, std::string type_)
{
    pos.x = x;
    pos.y = y;
    tileSize = size;
    textures = tileTextures;
    type = type_;
}

Tile::~Tile() 
{
}

Vector2 Tile::getPos() {
    return pos;
}

std::string Tile::getType() {
    return type;
}

void Tile::changeType(std::string newType) 
{
    type = newType;
}

void Tile::draw() 
{
    Texture2D texture = textures[type];
    DrawTextureEx(texture, pos, 0, 0.1, WHITE);
}