#include <vector>
#include <iostream>
#include "raylib.h"

#include "tile.h"


class Map
{
private:
    int rows, cols;
    std::vector<std::vector<Tile>> tileMap;
    
    Texture2D seaTile;
    Texture2D foodTile;
    Texture2D coralTile;
    Texture2D castleV1;
    Texture2D castleV2;
    Texture2D castleV3;
    Texture2D castleV4;
    Texture2D castleV5;

public:
    Map(int rowCount = 16, int columCount = 16);
    ~Map();
    void Draw();
};

Map::Map(int rowCount, int columCount)
{
    seaTile = LoadTexture("sprites/resources/BlankTile.png");
    foodTile = LoadTexture("sprites/resources/AlgenTile.png");
    coralTile = LoadTexture("sprites/resources/CoralTile.png");
    castleV1 = LoadTexture("sprites/castle/CastleTileLVL1.png"); 
    castleV2 = LoadTexture("sprites/castle/CastleTileLVL2.png");
    castleV3 = LoadTexture("sprites/castle/CastleTileLVL3.png");
    castleV4 = LoadTexture("sprites/castle/CastleTileLVL4.png");
    castleV5 = LoadTexture("sprites/castle/CastleTileLVL5.png");

    std::vector<Texture2D> tiles {seaTile, foodTile};

    rows = rowCount;
    cols = columCount;
    tileMap.resize(rows, std::vector<Tile>(cols, Tile(0, 0, 0.1, tiles))); // !!!! mogelijke optimalisatie en nog niet belangerijk TODO !!!! dit oplsosen zorgt ervoor dat alles 2 keer laat. inladen van textures ksot veel dus misschien pointers. 

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (i % 2 == 0) {
                tileMap.at(i).at(j) = Tile(i*1024/10, j*1024/10, 0.1, tiles); // tile location based on tiles with a size of 1024 x 1024
            } else {
                tileMap.at(i).at(j) = Tile(i*1024/10, j*1024/10-1024/20, 0.1, tiles);
            }
        }
    }

}

Map::~Map()
{
}

void Map::Draw() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            tileMap[i][j].Draw();
        }
    }
}