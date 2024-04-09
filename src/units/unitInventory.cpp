#include "unitInventory.h"

void UnitInventory::createUnit(Vector2 startingPos, Camera2D *test, int level, double statMultiplier) { // startingPos is grid position and not world position
    Tile *startTile = tileMap->getTile(startingPos);
    Texture2D *unitTexture;
    
    int maxHealth = 0;
    double damage = 0;
    double movementSpeed = 0;
    double defence = 0;

    Texture2D *texture = &unitTextures["warrior1LVL1"];

    if (owner == "player") {
        switch (level)
        {
        case 1:
            maxHealth = 100;
            damage = 10;
            movementSpeed = 30;
            defence = 5;
            texture = &unitTextures["warrior1LVL1"];
            break;
        case 2:
            maxHealth = 220;
            damage = 20;
            movementSpeed = 60;
            defence = 7;
            texture = &unitTextures["warrior1LVL2"];
            break;
        case 3:
            maxHealth = 450;
            damage = 34;
            movementSpeed = 30;
            defence = 15;
            texture = &unitTextures["warrior1LVL3"];
            break;
        case 4:
            maxHealth = 854;
            damage = 50;
            movementSpeed = 30;
            defence = 19;
            texture = &unitTextures["warrior1LVL4"];
            break;
        case 5:
            maxHealth = 1200;
            damage = 120;
            movementSpeed = 20;
            defence = 25;
            texture = &unitTextures["warrior1LVL5"];
            break;
        default:
            break;
        }
    } else {
        switch (level)
        {
        case 1:
            maxHealth = 100 * statMultiplier;
            damage = 10 * statMultiplier;
            movementSpeed = 30 * statMultiplier;
            defence = 5;
            texture = &unitTextures["warrior2LVL1"];
            break;
        case 2:
            maxHealth = 220 * statMultiplier;
            damage = 20 * statMultiplier;
            movementSpeed = 60 * statMultiplier;
            defence = 7;
            texture = &unitTextures["warrior2LVL2"];
            break;
        case 3:
            maxHealth = 450 * statMultiplier;
            damage = 34 * statMultiplier;
            movementSpeed = 30 * statMultiplier;
            defence = 15;
            texture = &unitTextures["warrior2LVL3"];
            break;
        case 4:
            maxHealth = 854 * statMultiplier;
            damage = 50 * statMultiplier;
            movementSpeed = 30 * statMultiplier;
            defence = 19;
            texture = &unitTextures["warrior2LVL4"];
            break;
        case 5:
            maxHealth = 1200 * statMultiplier;
            damage = 120 * statMultiplier;
            movementSpeed = 20 * statMultiplier;
            defence = 25;
            texture = &unitTextures["warrior2LVL5"];
            break;
        default:
            break;
        }
    }   

    Unit newUnit = Unit(maxHealth, defence, movementSpeed, damage, tileMap, test, startTile, startingPos, owner, texture, tileHighLite);
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

void UnitInventory::Update(double dt, Vector2 target) {
    removeDead();

    for (int i=0; i < units.size(); i++) {
        units.at(i).Update(dt, target);
    }
}

void UnitInventory::Update(double dt, bool overlay) {
    removeDead();

    for (int i=0; i < units.size(); i++) {
        units.at(i).Update(dt, overlay);
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

