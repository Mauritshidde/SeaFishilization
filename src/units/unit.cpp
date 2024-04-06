#include "unit.h"

void Unit::fight(Tile *targetTile) {
    Unit *enemy = targetTile->unitOnTile;
    
    // health -= enemy->attack();
    // enemy->health -= attack();
}

void Unit::heal() {

}

void Unit::takeDamage(double damage) 
{
    health -= damage;
}

void Unit::moveOneTile(int option) {
    // unitMoving = true;
        // movingDone = false;
        // movingProgress = 0;
        // unitMoving = false;
    // }
}

void Unit::move(Vector2 target) // target is given in hexagon coords
{
    Tile *targetTile = tileMap->getTile(target);

    // if (selected) {
    //     std::vector<Vector2> options = tileMap->getSurroundingCoords(gridPosition);
    //     for (int i=0; i < possibleOptions.size(); i++) {
    //         if (!tileMap->isTileLocked(options.at(i))) {
    //             possibleOptions.push_back(options.at(i));
    //         }
    //     }
    // }
    

    // if (!targetTile->isUnitOnTile) {
    //     position = target;
    //     currentTile->isUnitOnTile = false;
    //     currentTile->unitOnTile = NULL;

    //     targetTile->unitOnTile = this;
    //     targetTile->isUnitOnTile = true;
    // } else {
    //     fight(targetTile);
    // }


    // bool unitMoving = false;

    // if (unitMoving) {
    //     // pathfinding

    //     moveOneTile(1);
    // }

}

void Unit::setOptions() {
    std::vector<Vector2> options = tileMap->getSurroundingCoords(gridPosition);
    for (int i=0; i < options.size(); i++) {
        if (!tileMap->isTileLocked(options.at(i))) {
            possibleOptions.push_back(options.at(i));
        }
    }
}

void Unit::removeOptions() {
    for (int i=0; i < possibleOptions.size(); i++) {
        possibleOptions.pop_back();
    }
}

// void Unit::removeOptions() {
//     for (int i=0; i < possibleOptions.size(); i++) {
//         possibleOptions.pop_back();
//     }
// }

bool Unit::tileInOptions(Vector2 coords) {
    for (int i=0; i < possibleOptions.size(); i++) {
        Vector2 possibleCoord = possibleOptions.at(i);
        if (coords.x == possibleCoord.x && coords.y == possibleCoord.y) {
            return true;
        }
    }
    return false;
}

void Unit::Update(double dt)
{
    if (selected) {
        if (IsMouseButtonPressed(0)) {
            Vector2 mousePos = GetMousePosition();
            Vector2 tilePos = tileMap->worldPosToGridPos(GetScreenToWorld2D(mousePos, *camera));

            if (tilePos.x == gridPosition.x && tilePos.y == gridPosition.y) {
                selected = false;
                removeOptions();
            } else if (tileInOptions(tilePos)) {
                selected = false;
                gridPosition = tilePos;

                currentTile->isUnitOnTile = false;
                currentTile->unitOnTile = NULL;

                Tile *targetTile = tileMap->getTile(tilePos);

                targetTile->isUnitOnTile = true;
                targetTile->unitOnTile = this;

                currentTile = targetTile;
                
                removeOptions();
            }
        }
    } else {
        if (IsMouseButtonPressed(0)) {
            Vector2 mousePos = GetMousePosition();
            Vector2 tilePos = tileMap->worldPosToGridPos(GetScreenToWorld2D(mousePos, *camera));
            if (tilePos.x == gridPosition.x && tilePos.y == gridPosition.y) {
                selected = true;
                setOptions();
            }
        }
    }

    position = tileMap->gridPosToWorldPos(gridPosition);


    // } else {
    //     std::cout << "ja" << std::endl;
    //     for (int i=0; i < possibleOptions.size(); i++) {
    //         possibleOptions.pop_back();
    //     }
    // }
    // if (inBattle) {

    // }


    // checkIfMovementPossible(); // returns true if possible input is the option

    // if (unitMoving) {
    //     movingProgress += movementSpeed * dt;
    // }

    // if (movingProgress >= 100) {
    //     movingDone = true;
    //     moveOneTile(option);
    // }
}

void Unit::Render()
{
    for (int i=0; i < possibleOptions.size(); i++) {
        // std::cout << i << " werkt" << std::endl;
        Tile *tile = tileMap->getTile(possibleOptions.at(i));
        DrawTextureEx(tileHighLite, tile->getPos(), 0, (double) tileMap->tileHeight / 810, WHITE);
    }

    DrawTextureEx(texture, position, 0, 0.1, WHITE);
}

Unit::Unit(double setMaxHealth, double setAttackSpeed, double setMovementSpeed, double setAttackDamage, Map *setTileMap, Camera2D* setCamera, Tile *startTile)
{
    maxHealth = setMaxHealth;
    attackSpeed = setMaxHealth;
    movementSpeed = setMovementSpeed;
    attackDamage = setAttackDamage;

    selected = false;
    health = setMaxHealth;
    gridPosition = {10,10};

    tileMap = setTileMap;
    camera = setCamera;
    currentTile = startTile;

    // currentTile->isUnitOnTile = true;
    // currentTile->unitOnTile = this;

    texture = LoadTexture("sprites/units/melee/Battlefish.png");
    tileHighLite = LoadTexture("sprites/UI-elements/hexHighlight.png");
}

Unit::~Unit()
{

}
        
