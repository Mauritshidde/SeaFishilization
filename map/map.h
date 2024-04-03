#include <vector>
#include <iostream>

#include "tile.h"


class Map
{
private:
    int rows, cols;
    std::vector<std::vector<Tile>> tileMap;
public:
    Map(int rowCount = 16, int columCount = 16);
    ~Map();
    void Draw();
};

Map::Map(int rowCount, int columCount)
{
    rows = rowCount;
    cols = columCount;
    tileMap.resize(rows, std::vector<Tile>(cols, Tile(0, 0)));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            tileMap[i][j] = Tile(i, j, 100);
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