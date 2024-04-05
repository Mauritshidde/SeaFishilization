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

    Vector2 getPos();
    std::string getType();
    void changeType(std::string newType);
    void draw();
    Tile(int x, int y, int w, int h, std::map<std::string, Texture2D>& tileTextures, std::string type_);
    ~Tile();
};

Tile::Tile(int x, int y, int w, int h, std::map<std::string, Texture2D>& tileTextures, std::string type_)
{
    unitOnTile = NULL;
    isUnitOnTile = false;

    pos.x = x;
    pos.y = y;
    width = w;
    height = h;
    textures = tileTextures;
    type = type_;
}

Tile::~Tile() 
{
}

Vector2 Tile::getPos() {
    return pos;
}

std::string Tile::getType() {
    return type;
}

void Tile::changeType(std::string newType) 
{
    type = newType;
}

void Tile::draw() 
{
    Texture2D texture = textures[type];
    double scale = (double) height / 810;
    DrawTextureEx(texture, pos, 0, scale, WHITE);
}