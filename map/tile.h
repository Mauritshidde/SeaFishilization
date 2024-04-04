#include <map>
#include <string>
#include "../raylib.h"

class Tile 
{
private: 
    int tileSize;
    int type;
    Texture2D tileTexture;

    void changeTile();
public:
    Vector2 pos;

    void changeType(int newType);
    void Draw();
    Tile(int x, int y, double size, std::map<std::string, Texture2D> tileTextures);
    ~Tile();
};

void Tile::changeTile() {

}

void Tile::changeType(int newType) {
    changeTile();
}

Tile::Tile(int x, int y, double size, std::map<std::string, Texture2D> tileTextures)
{
    pos.x = x;
    pos.y = y;
    tileSize = size;
    tileTexture = tileTextures["sea"];
}

void Tile::Draw() 
{
    DrawTextureEx(tileTexture, pos, 0, 0.1, WHITE);
}

Tile::~Tile() {

}