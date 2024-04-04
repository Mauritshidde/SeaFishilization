#include <map>
#include <string>
#include "../raylib.h"

class Tile 
{
private: 
    int tileSize;
    std::string type;
    std::map<std::string, Texture2D> textures;


public:
    Vector2 pos;

    void changeType(std::string newType);
    void draw();
    Tile(int x, int y, double size, std::map<std::string, Texture2D>& tileTextures, std::string type);
    ~Tile();
};

void Tile::changeType(std::string newType) {
    type = newType;
}

Tile::Tile(int x, int y, double size, std::map<std::string, Texture2D>& tileTextures, std::string type_)
{
    pos.x = x;
    pos.y = y;
    tileSize = size;
    textures = tileTextures;
    type = type_;
}

void Tile::draw() 
{
    Texture2D texture = textures[type];
    DrawTextureEx(texture, pos, 0, 0.1, WHITE);
}

Tile::~Tile() {

}