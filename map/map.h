#include <vector>
#include <iostream>

#include "tile.h"


class Map
{
private:
    int rows, cols;
    std::vector<std::vector<Tile>> tileMap;
    
    Texture2D seaTile;
    Texture2D foodTile;
    Texture2D coralTile;
public:
    Map(int rowCount = 16, int columCount = 16);
    ~Map();
    void Draw();
};

Map::Map(int rowCount, int columCount)
{
    rows = rowCount;
    cols = columCount;
    tileMap.resize(rows, std::vector<Tile>(cols, sizeof(Tile()))); // !!!! mogelijke optimalisatie en nog niet belangerijk TODO !!!! dit oplsosen zorgt ervoor dat alles 2 keer laat. inladen van textures ksot veel dus misschien pointers. 

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (i % 2 == 0) {
                tileMap.at(i).at(j) = Tile(i*1024/10, j*1024/10, 0.1); // tile location based on tiles with a size of 1024 x 1024
            } else {
                tileMap.at(i).at(j) = Tile(i*1024/10, j*1024/10-1024/20, 0.1);
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