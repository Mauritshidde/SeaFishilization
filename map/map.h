#include <vector>
#include <iostream>
#include <cmath>
#include "raylib.h"

#include "tile.h"


class Map
{
private:
    Camera2D *playerCamera;

    int rows, cols;
    double tileSize;
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
    Vector2 worldPosToGridPos(Vector2 coord);
    Map(int rowCount = 16, int columCount = 16, Camera2D *setPlayerCamera = NULL);
    ~Map();
    void Draw();
};

Map::Map(int rowCount, int columCount, Camera2D *setPlayerCamera)
{
    playerCamera = setPlayerCamera;

    seaTile = LoadTexture("sprites/resources/BlankTile.png");
    foodTile = LoadTexture("sprites/resources/AlgenTile.png");
    coralTile = LoadTexture("sprites/resources/CoralTile.png");
    castleV1 = LoadTexture("sprites/castle/CastleTileLVL1.png"); 
    castleV2 = LoadTexture("sprites/castle/CastleTileLVL2.png");
    castleV3 = LoadTexture("sprites/castle/CastleTileLVL3.png");
    castleV4 = LoadTexture("sprites/castle/CastleTileLVL4.png");
    castleV5 = LoadTexture("sprites/castle/CastleTileLVL5.png");

    std::vector<Texture2D> tiles {seaTile, foodTile};

    tileSize = 1024/10;
    rows = rowCount;
    cols = columCount;
    tileMap.resize(rows, std::vector<Tile>(cols, Tile(0, 0, 0.1, tiles))); 
    
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (i % 2 == 0) {
                tileMap.at(i).at(j) = Tile(i*tileSize, j*tileSize, 0.1, tiles); // tile location based on tiles with a size of 1024 x 1024
            } else {
                tileMap.at(i).at(j) = Tile(i*tileSize, j*tileSize-tileSize/2, 0.1, tiles);
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

Vector2 Map::worldPosToGridPos(Vector2 coord) { // coordinate of mouse  to grid
    int x = coord.x/(tileSize);
    int y;
    // std::cout << x << " x " << coord.x/(tileSize) << std::endl;

    if (x % 2 == 0) {
        y = coord.y/(tileSize);
        // std::cout << y << " y " << coord.y/(tileSize) << std::endl;
    } else {
        y = std::round(coord.y/(tileSize) + 1/2);
        // std::cout << y << " y " << coord.y/(tileSize) + 1/2 << std::endl;
    }

    Vector2 result;
    result.x = x;
    result.y = y;

    return result;
}