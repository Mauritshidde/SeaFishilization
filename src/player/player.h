#pragma once
#include <string>
#include "../raylib.h"
#include "../map/map.h"
#include "../units/unit.h"
#include "../units/unitInventory.h"

class Player
{
private:
    double movementSpeed;
    double zoomSpeed;
    double mouseMovementSpeed;
    double minZoom;
    double maxZoom;
    double maxX, minX;
    double maxY, minY;

    UnitInventory playerUnits;
    Vector2 mouseStartPos;

    int screenWidth;
    int screenHeight;

    int food;
    int coral;

    std::vector<Unit> units;
    Map *map;
public:

    Camera2D camera = { 0 };
    Vector2 position;
    void addFoodAmount(int amount); // remove food if buying something add food when receiving something
    void addCoralAmount(int amount); // remove coral if buying something add coral when receiving something
    void movement(double dt);
    int getFoodAmount();
    int getCoralAmount();
    bool buyTile(std::string type);

    void Update(double dt);

    Player(Vector2 startPosition={0,0}, int screenWidth=1920, int screenHeight=1080, Map *setMap = NULL);
    ~Player();
};