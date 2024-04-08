#include "map.h"

Map::Map(int rowCount, int columnCount, std::map<std::string, Texture2D> tileTextures_) 
{
    rows = rowCount;
    cols = columnCount;
    tileTextures = tileTextures_;

    lockedTileTypes = {
        "locked",
        "castleV1",
        "castleV2",
        "castleV3",
        "castleV4",
        "castleV5"
    };

    whiteHighlightTileTexture = LoadTexture("sprites/UI-elements/hexHighlight.png");
    redHighlightTileTexture = LoadTexture("sprites/UI-elements/hexRedHighlight.png");

    tileWidth = 100;
    tileHeight = 115;
    tileMap.resize(rows, std::vector<Tile>(cols, Tile(0, 0, 0.13, 0.13, tileTextures, "sea" ))); 
    
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (i % 2 == 0) {
                tileMap.at(i).at(j) = Tile(i*tileWidth, j*tileHeight, tileWidth, tileHeight, tileTextures, "sea"); // tile location based on tiles with a size of 1024 x 1024
            } else {
                tileMap.at(i).at(j) = Tile(i*tileWidth, j*tileHeight-tileHeight/2, tileWidth, tileHeight, tileTextures, "sea");
            }
        }
    }
    tileMap.at(rows/2).at(cols/2).changeType("castleV1");
}

Map::~Map()
{

}

Tile* Map::getTile(Vector2 coord) {
    if(coord.y >= rows) {
        coord.y = rows - 1;
    }
    if (coord.x >= cols) {
        coord.x = cols - 1;
    }
    if (coord.y < 0) {
        coord.y = 0;
    }
    if (coord.x < 0) {
        coord.x = 0;
    }
    return &tileMap.at(coord.x).at(coord.y);
}

void Map::draw() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            tileMap.at(i).at(j).draw();
        }
    }
}

void Map::drawGhostTile(Vector2 coord, std::string type, bool isPlacementAllowed) 
{
    Texture2D texture = tileTextures[type];

    Tile* tile = getTile(coord);

    bool isInLockedTileTypes = (std::find(lockedTileTypes.begin(), lockedTileTypes.end(), tile->getType()) != lockedTileTypes.end());
    if(isInLockedTileTypes) {
        return;
    }

    Vector2 pos = tile->getPos();
    double scale = (double) tileHeight / 810;
    DrawTextureEx(texture, pos, 0, scale, WHITE);
    if(isPlacementAllowed) {
        DrawTextureEx(whiteHighlightTileTexture, tile->getPos(), 0, (double) tileHeight / 810, WHITE);
    } else {
        DrawTextureEx(redHighlightTileTexture, tile->getPos(), 0, (double) tileHeight / 810, WHITE);
    }
    
    tile = NULL;
}

std::string Map::getTileType(Vector2 coord) {
    Tile* tile = getTile(coord);
    return tile->getType();
} 

bool Map::isTileAvailable(Vector2 coord, std::string type) {
    bool isInLockedTileTypes = (std::find(lockedTileTypes.begin(), lockedTileTypes.end(), getTileType(coord)) != lockedTileTypes.end());
    if(isInLockedTileTypes || getTileType(coord) == type) {
        return false;
    }
    return true;
}

bool Map::isTileLocked(Vector2 coord) {
    bool isInLockedTileTypes = (std::find(lockedTileTypes.begin(), lockedTileTypes.end(), getTileType(coord)) != lockedTileTypes.end());
    return isInLockedTileTypes;
}

void Map::changeTileType(Vector2 coord, std::string type) {
    Tile *useTile = getTile(coord);
    useTile->changeType(type);
}

Vector2 Map::worldPosToGridPos(Vector2 coord) 
{ // coordinate of mouse  to grid
    int x = coord.x/(tileWidth);
    int y;

    if (x % 2 == 0) {
        y = coord.y/(tileHeight);
    } else {
        y = std::round(coord.y/(tileHeight) + 1/2);
    }

    Vector2 result;
    result.x = x;
    result.y = y;

    return result;
}

Vector2 Map::gridPosToWorldPos(Vector2 coord) 
{ // coordinate of mouse  to grid
    int x = coord.x*(tileWidth);
    int y;

    if (x % 2 == 0) {
        y = coord.y*(tileHeight);
    } else {
        y = std::round((coord.y+0.5) * tileHeight);
    }

    Vector2 result;
    result.x = x;
    result.y = y;

    return result;
}

std::vector<Vector2> Map::getSurroundingCoordsEnemy(Vector2 coord) 
{
    std::vector<Vector2> surroundingCoords;
    if(coord.x < 0 || coord.x > rows - 1 || coord.y < 0 || coord.y > cols - 1) {
        // ? excluding gameBorder tiles: always locked //
        return surroundingCoords;
    }
    
    if((int)coord.x % 2 == 1) {
        surroundingCoords = {
            { coord.x, coord.y - 1 },
            { coord.x + 1, coord.y - 1 },
            { coord.x + 1, coord.y },
            { coord.x, coord.y + 1 },
            { coord.x - 1, coord.y },
            { coord.x - 1, coord.y - 1}
        };
    } else {
        surroundingCoords = {
            { coord.x, coord.y - 1 },
            { coord.x + 1, coord.y },
            { coord.x + 1, coord.y + 1 },
            { coord.x, coord.y + 1 },
            { coord.x - 1, coord.y + 1 },
            { coord.x - 1, coord.y}
        };
    }
    return surroundingCoords;
}

std::vector<Vector2> Map::getSurroundingCoords(Vector2 coord) 
{
    std::vector<Vector2> surroundingCoords;
    if(coord.x < 1 || coord.x > rows - 2 || coord.y < 1 || coord.y > cols - 2) {
        // ? excluding gameBorder tiles: always locked //
        return surroundingCoords;
    }
    
    if((int)coord.x % 2 == 1) {
        surroundingCoords = {
            { coord.x, coord.y - 1 },
            { coord.x + 1, coord.y - 1 },
            { coord.x + 1, coord.y },
            { coord.x, coord.y + 1 },
            { coord.x - 1, coord.y },
            { coord.x - 1, coord.y - 1}
        };
    } else {
        surroundingCoords = {
            { coord.x, coord.y - 1 },
            { coord.x + 1, coord.y },
            { coord.x + 1, coord.y + 1 },
            { coord.x, coord.y + 1 },
            { coord.x - 1, coord.y + 1 },
            { coord.x - 1, coord.y}
        };
    }
    return surroundingCoords;
}

bool Map::isSurrounded(Vector2 coord) {
    std::vector<std::string> buildTileTypes = {
        "food",
        "coral",
        "training",
        "castleV1",
        "castleV2",
        "castleV3",
        "castleV4",
        "castleV5"
    };

    std::vector<Vector2> surroundingCoords = getSurroundingCoords(coord);
    for(int i = 0; i < surroundingCoords.size(); i++) {
        bool isInBuildTileTypes = 
            (std::find(buildTileTypes.begin(), buildTileTypes.end(), getTileType(surroundingCoords.at(i))) != buildTileTypes.end());
        
        if(isInBuildTileTypes) {
            return true;
        }
    }
    return false;
}

int Map::countTilesWithType(std::string type) {
    int count = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (getTileType({i, j}) == type) {
                count++;
            }
        }
    }
    return count;
}
