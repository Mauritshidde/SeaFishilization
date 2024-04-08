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

    int castleLvl;
    int castleCost;


    std::vector<Unit> units;
    Map *map;

    std::map<std::string, Texture2D> unitTextures;
    Texture2D *tileHighLite;
    int productionSpeed;
public:

    Camera2D camera = { 0 };
    Vector2 position;
    void addFoodAmount(int amount); // remove food if buying something add food when receiving something
    void addCoralAmount(int amount); // remove coral if buying something add coral when receiving something
    void movement(double dt, int isBuildMode);
    int getFoodAmount();
    int getCoralAmount();
    int getTileCost(std::string type);
    bool buyTile(std::string type);
    bool buyCastleUpgrade();
    int getCastleLvl();

    void Update(double dt, int isBuildMode);
    void Render();
    void Start();

    Player(Vector2 startPosition={0,0}, int screenWidth=1920, int screenHeight=1080, Map *setMap = NULL, Texture2D *setTileHighLite = NULL, std::map<std::string, Texture2D> setUnitTextures = {});
    ~Player();
};