#include "unit.h"

void Unit::fight(Tile *targetTile, double dt) {
    Unit *enemy = targetTile->unitOnTile;
    
    double *enemyHealth = &enemy->health;

    *enemyHealth -= attackDamage * dt;
    health -= enemy->attackDamage * dt;

    if (*enemyHealth <= 0) {
        currentTile->unitOnTile = NULL;
        currentTile->isUnitOnTile = false;

        targetTile->unitOnTile = this;
        currentTile = targetTile;
        enemy->isAlive = false;
    }
    
    if (health <= 0) {
        currentTile->unitOnTile = NULL;
        currentTile->isUnitOnTile = false;

        currentTile = NULL;   
        isAlive = false;
    }

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

// void Unit::move(Vector2 target) // target is given in hexagon coords
// {
//     Tile *targetTile = tileMap->getTile(target);

//     // if (selected) {
//     //     std::vector<Vector2> options = tileMap->getSurroundingCoords(gridPosition);
//     //     for (int i=0; i < possibleOptions.size(); i++) {
//     //         if (!tileMap->isTileLocked(options.at(i))) {
//     //             possibleOptions.push_back(options.at(i));
//     //         }
//     //     }
//     // }
    

//     // if (!targetTile->isUnitOnTile) {
//     //     position = target;
//     //     currentTile->isUnitOnTile = false;
//     //     currentTile->unitOnTile = NULL;

//     //     targetTile->unitOnTile = this;
//     //     targetTile->isUnitOnTile = true;
//     // } else {
//     //     fight(targetTile);
//     // }


//     // bool unitMoving = false;

//     // if (unitMoving) {
//     //     // pathfinding

//     //     moveOneTile(1);
//     // }

// }

bool Unit::hasTileEnemy(Vector2 coord, std::string type) {
    Tile *tile = tileMap->getTile(coord);
    if (tile->isUnitOnTile) {
        if (tile->unitOnTile->owner != type) {
            return true;
        }
    } else {
        return false;
    }

    return false; // just to be sure for the compiler
}

bool Unit::hasTileFriendly(Vector2 coord, std::string type) {
    Tile *tile = tileMap->getTile(coord);
    if (tile->isUnitOnTile) {
        if (tile->unitOnTile->owner == type) {
            return true;
        }
    } else {
        return false;
    }

    return false; // just to be sure for the compiler
}

// void Unit::removeBorderOptions() {
//     if() {
//         return surroundingCoords;
//     }
// }

void Unit::setOptions() {
    std::vector<Vector2> options = tileMap->getSurroundingCoords(gridPosition);
    for (int i=0; i < options.size(); i++) {
        Vector2 coord = options.at(i);
        if (!tileMap->isTileLocked(coord) && !hasTileFriendly(coord, owner)) {
            bool isBorder = (coord.x < 1 || coord.x > tileMap->rows - 2 || coord.y < 1 || coord.y > tileMap->cols - 2);
            if (!isBorder) {
                possibleOptions.push_back(options.at(i));
            }
        }
    }
}

void Unit::removeOptions() {
    int size = possibleOptions.size();
    for (int i=0; i < size; i++) {
        possibleOptions.pop_back();
    }
}

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
    if (!currentTile->isUnitOnTile) { // only place that this can be done, in constructor it doesn't change the value for some reason
        currentTile->isUnitOnTile = true;
        currentTile->unitOnTile = this;
    }

    // if (!isMoving) {
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
                } else {
                    removeOptions();
                    selected = false;
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
        position = {position.x + 0.35 * tileMap->tileWidth, position.y + 0.1 * tileMap->tileHeight};
    // } else {
        // smooth movement

        // isMoving = false;
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
        Tile *tile = tileMap->getTile(possibleOptions.at(i));
        DrawTextureEx(*tileHighLite, tile->getPos(), 0, (double) tileMap->tileHeight / 810, WHITE);
    }

    if (int(gridPosition.x) % 2 == 0) {
        DrawTextureEx(*texture, position, 0, 0.1, WHITE);
    } else {
        DrawTextureEx(*texture, {position.x, position.y - 0.5 * tileMap->tileHeight}, 0, 0.1, WHITE);
    }
}

Unit::Unit(double setMaxHealth, double setAttackSpeed, double setMovementSpeed, double setAttackDamage, Map *setTileMap, Camera2D* setCamera, Tile *startTile, Vector2 startingGridPos, std::string setOwner, Texture2D *setTexture, Texture2D *setTileHighLite)
{
    maxHealth = setMaxHealth;
    attackSpeed = setMaxHealth;
    movementSpeed = setMovementSpeed;
    attackDamage = setAttackDamage;

    selected = false;
    health = setMaxHealth;
    gridPosition = startingGridPos;

    tileMap = setTileMap;
    camera = setCamera;
    currentTile = startTile;

    isMoving = false;
    canMove = true;
    isAlive = true;

    owner = setOwner;

    texture = setTexture;
    tileHighLite = setTileHighLite;
}

Unit::~Unit()
{

}
        
