#pragma once
#include <map>
#include <string>
#include "../raylib.h"

#include "../units/unit.h"


class Tile 
{
private: 
    int width;
    int height;
    std::string type;
    std::map<std::string, Texture2D> textures;
    Vector2 pos;

public:
    Unit *unitOnTile;
    bool isUnitOnTile;
    // bool tileSelected;

    Vector2 getPos();
    std::string getType();
    void changeType(std::string newType);
    void draw();
    Tile(int x, int y, int w, int h, std::map<std::string, Texture2D>& tileTextures, std::string type_);
    ~Tile();
};