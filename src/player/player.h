#pragma once
#include <string>
#include "../raylib.h"

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

    Vector2 mouseStartPos;

    int screenWidth;
    int screenHeight;

    int food;
    int coral;
public:

    Camera2D camera = { 0 };
    Vector2 position;
    void addFoodAmount(int amount); // remove food if buying something add food when receiving something
    void addCoralAmount(int amount); // remove coral if buying something add coral when receiving something
    void movement(double dt);
    int getFoodAmount();
    int getCoralAmount();
    bool buyTile(std::string type);

    Player(Vector2 startPosition={0,0}, int screenWidth=1920, int screenHeight=1084);
    ~Player();
};