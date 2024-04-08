#pragma once
#include <vector>
#include <string>
#include <map>
#include "../raylib.h"

#include "../map/tile.h"
#include "../map/map.h"
#include "unit.h"

class UnitInventory
{
private:
    bool isAlive(Unit *unit);
    void removeDead();

    Map *tileMap;
    Camera2D *camera;

    std::map<std::string, Texture2D> unitTextures;
    Texture2D *tileHighLite;
public:
    std::string owner;
    std::vector<Unit> units;

    void createUnit(int maxHealth, double damage, double movementSpeed, Vector2 startingPos, Camera2D *test);
    void Update(double dt);
    void Render();

    UnitInventory(std::string setOnwer = "player", Map *setMap = NULL, Camera2D *setCamera = NULL, Texture2D *setTileHighLite = NULL, std::map<std::string, Texture2D> setUnitTextures = {});
    ~UnitInventory();
};