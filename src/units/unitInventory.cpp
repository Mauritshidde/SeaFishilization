#include "unitInventory.h"

void UnitInventory::createUnit(int maxHealth, double damage, double movementSpeed, std::string onwer, Vector2 startingPos) { // startingPos is grid position and not world position
    Tile *startTile = map->getTile(startingPos);
    Unit newUnit = Unit(maxHealth, 1, movementSpeed, damage, map, camera, startTile);
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
}

UnitInventory::UnitInventory(std::string setOnwer, Map *setMap, Camera2D *setCamera)
{
    owner = setOnwer;
    map = setMap;
    camera = setCamera;
}

UnitInventory::~UnitInventory()
{
    
}

