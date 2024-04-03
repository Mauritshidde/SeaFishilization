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
    Tile(int x = 0, int y = 0, int size = 30);
    ~Tile();
};

Tile::Tile(int x, int y, int size) 
{
    pos.x = x;
    pos.y = y;
    tileSize = size;
    // tileTexture = LoadTexture("hexagon.png");
}

void Tile::Draw() 
{
    Color tileColor = {110, 125, 150, 255}; // temp
    DrawRectangle(pos.x * tileSize, pos.y * tileSize, tileSize -1, tileSize -1, tileColor);
}

Tile::~Tile() {

}