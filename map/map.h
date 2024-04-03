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
            if (i % 2 == 0) {
                tileMap[i][j] = Tile(i*1024/10, j*1024/10, 100);
                std::cout << "ja" << std::endl;
            } else {
                tileMap[i][j] = Tile(i*1024/10, j*1024/10-1024/20, 100);
                std::cout << "nee" << std::endl;
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