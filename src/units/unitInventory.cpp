#include "unitInventory.h"

void UnitInventory::createUnit(int maxHealth, double damage, double movementSpeed, Vector2 startingPos, Camera2D *test) { // startingPos is grid position and not world position
    Tile *startTile = tileMap->getTile(startingPos);
    Unit newUnit = Unit(maxHealth, 1, movementSpeed, damage, tileMap, test, startTile, startingPos, owner, &unitTextures["warrior1LVL1"], tileHighLite);
    units.push_back(newUnit);
}


bool UnitInventory::isAlive(Unit *unit) {
    if (unit->isAlive) {
        return true;
    } else {
        return false;
    }
}

void UnitInventory::removeDead() {
    int vecSize = units.size();
    int amountDeleted = 0;
    for (int i=0; i < vecSize; i++) {
        if (!isAlive(&units.at(i-amountDeleted))) {
            units.erase(std::next(units.begin(), i-amountDeleted));
            amountDeleted++;
        }   
    }
}

void UnitInventory::Update(double dt) {
    removeDead();

    for (int i=0; i < units.size(); i++) {
        units.at(i).Update(dt);
    }
}

void UnitInventory::Render() {
    for (int i=0; i < units.size(); i++) {
        units.at(i).Render();
    }
}


UnitInventory::UnitInventory(std::string setOnwer, Map *setMap, Camera2D *setCamera, Texture2D *setTileHighLite, std::map<std::string, Texture2D> setUnitTextures)
{
    owner = setOnwer;
    tileMap = setMap;
    camera = setCamera;

    tileHighLite = setTileHighLite;
    unitTextures = setUnitTextures;
}

UnitInventory::~UnitInventory()
{
    tileMap = NULL;
    camera = NULL;

    tileHighLite = NULL;
}

