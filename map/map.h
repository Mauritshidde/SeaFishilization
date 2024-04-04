#include <vector>
#include <iostream>
#include <cmath>
#include <map>
#include <string>
#include "../raylib.h"

#include "tile.h"


class Map
{
private:
    Camera2D *playerCamera;

    int rows, cols;
    double tileSize;
    std::vector<std::vector<Tile>> tileMap;
    
    std::map<std::string, Texture2D> tileTextures;
    // Texture2D seaTile;
    // Texture2D foodTile;
    // Texture2D coralTile;
    // Texture2D castleV1;
    // Texture2D castleV2;
    // Texture2D castleV3;
    // Texture2D castleV4;
    // Texture2D castleV5;

public:
    Vector2 worldPosToGridPos(Vector2 coord);
    void draw();
    Map(int rowCount = 16, int columCount = 16, Camera2D *setPlayerCamera = NULL);
    ~Map();
};

Map::Map(int rowCount, int columCount, Camera2D *setPlayerCamera) 
{
    rows = rowCount;
    cols = columCount;
    playerCamera = setPlayerCamera;

    // TODO get sprites as parameter in map constructor //
    tileTextures = {
        {"locked", LoadTexture("sprites/resources/BlankTile.png")},
        {"sea", LoadTexture("sprites/resources/BlankTile.png")},
        {"food", LoadTexture("sprites/resources/AlgenTile.png")},
        {"coral", LoadTexture("sprites/resources/CoralTile.png")},
        {"castleV1", LoadTexture("sprites/castle/CastleTileLVL1.png")},
        {"castleV2", LoadTexture("sprites/castle/CastleTileLVL2.png")},
        {"castleV3", LoadTexture("sprites/castle/CastleTileLVL3.png")},
        {"castleV4", LoadTexture("sprites/castle/CastleTileLVL4.png")},
        {"castleV5", LoadTexture("sprites/castle/CastleTileLVL5.png")}
    };

    tileSize = 1024/10;
    tileMap.resize(rows, std::vector<Tile>(cols, Tile(0, 0, 0.1, tileTextures, "sea" ))); 
    
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (i % 2 == 0) {
                tileMap.at(i).at(j) = Tile(i*tileSize, j*tileSize, 0.1, tileTextures, "sea"); // tile location based on tiles with a size of 1024 x 1024
            } else {
                tileMap.at(i).at(j) = Tile(i*tileSize, j*tileSize-tileSize/2, 0.1, tileTextures, "sea");
            }
        }
        tileMap.at(rows/2).at(cols/2).changeType("castleV1");
    }
}

Map::~Map()
{
}

void Map::draw() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            tileMap[i][j].draw();
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