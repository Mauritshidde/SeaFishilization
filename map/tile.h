#include "raylib.h"

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
    Tile(int x, int y, double size, std::vector<Texture2D> setTileTexture);
    ~Tile();
};

void Tile::changeTile() {

}

void Tile::changeType(int newType) {
    changeTile();
}

Tile::Tile(int x, int y, double size, std::vector<Texture2D> setTileTexture)
{
    pos.x = x;
    pos.y = y;
    tileSize = size;
    tileTexture = setTileTexture.at(0); // change to vec
}

void Tile::Draw() 
{
    DrawTextureEx(tileTexture, pos, 0, 0.1, WHITE);
}

Tile::~Tile() {

}