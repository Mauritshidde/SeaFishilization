#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
#include <string>
#include "../raylib.h"

#include "tile.h"

class Map
{
private:
    std::vector<std::vector<Tile>> tileMap;
    std::vector<std::string> lockedTileTypes;
    
    std::map<std::string, Texture2D> tileTextures;
    Texture2D whiteHighlightTileTexture;
    Texture2D redHighlightTileTexture;
    
public:
    int rows, cols;
    int tileHeight, tileWidth;
    Vector2 worldPosToGridPos(Vector2 coord);
    Vector2 gridPosToWorldPos(Vector2 coord);
std::vector<Vector2> getBorders();
    std::vector<Vector2> getSurroundingCoords(Vector2 coord);
    std::vector<Vector2> getSurroundingCoordsEnemy(Vector2 coord);
    bool isSurrounded(Vector2 coord);
    void drawGhostTile(Vector2 coord, std::string type, bool isPlacementAllowed);
    std::string getTileType(Vector2 coord);
    bool isTileAvailable(Vector2 coord, std::string type);
    bool isTileLocked(Vector2 coord);
    void changeTileType(Vector2 coord, std::string type);
    int countTilesWithType(std::string type);
    void draw();
    Tile* getTile(Vector2 coord);

    Map(int rowCount = 17, int columnCount = 17, std::map<std::string, Texture2D> tileTextures_ = std::map<std::string, Texture2D>());
    ~Map();
};