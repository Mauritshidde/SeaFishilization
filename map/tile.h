#include "raylib.h"

class Tile 
{
private: 
    int tileSize;
    int type;
    Texture2D tileTexture;
public:
    Vector2 pos;

    void Draw();
    Tile(int x = 0, int y = 0, double size = 0.1);
    ~Tile();
};

Tile::Tile(int x, int y, double size) 
{
    pos.x = x;
    pos.y = y;
    tileSize = size;
    tileTexture = LoadTexture("sprites/resources/BlankTile.png");
}

void Tile::Draw() 
{
    DrawTextureEx(tileTexture, pos, 0, tileSize, WHITE);
}

Tile::~Tile() {

}