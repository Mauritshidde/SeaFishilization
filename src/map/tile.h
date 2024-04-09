#pragma once
#include <map>
#include <string>
#include "../raylib.h"

// #include "../units/unit.h"

// Forward declaration of Unit class, because of cicular dependicy
class Unit;

class Tile 
{
private: 
    std::string type;
    std::map<std::string, Texture2D> textures;
    Vector2 pos;

public:
    Unit *unitOnTile;
    bool isUnitOnTile;
    bool tileSelected;
    bool isAccesible;
    bool isTraining;

    int width;
    int height;
    
    Vector2 getPos();
    std::string getType();
    void changeType(std::string newType);
    void draw();
    Tile(int x, int y, int w, int h, std::map<std::string, Texture2D>& tileTextures, std::string type_);
    ~Tile();
};