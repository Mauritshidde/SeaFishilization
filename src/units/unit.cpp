#include "unit.h"

void Unit::fight(Tile *targetTile, double dt) {
    Unit *enemy = targetTile->unitOnTile;
    double *enemyHealth = &enemy->health;
    int damage = 0;


    damage = attackDamage - enemy->defence; // calc damage with defence
    if (damage < 0) {
        damage = 0;
    }
    *enemyHealth -= damage * dt;

    
    damage = enemy->attackDamage - defence;
    if (damage < 0) {
        damage = 0;
    }
    health -= damage * dt;


    if (*enemyHealth <= 0) {
        currentTile->unitOnTile = NULL;
        currentTile->isUnitOnTile = false;

        targetTile->unitOnTile = this;
        currentTile = targetTile;
        enemy->isAlive = false;
        isMoving = false;
        targetTile->isAccesible = true;
    }
    
    if (health <= 0) {
        currentTile->unitOnTile = NULL;
        currentTile->isUnitOnTile = false;

        currentTile = NULL;   
        isAlive = false;
        isMoving = false;
        targetTile->isAccesible = true;
        targetTile->unitOnTile->canMove = true;
    }
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

void Unit::setOptions() {
    std::vector<Vector2> options = tileMap->getSurroundingCoordsEnemy(gridPosition);
    for (int i=0; i < options.size(); i++) {
        Vector2 coord = options.at(i);
        if (!tileMap->isTileLocked(coord) && !hasTileFriendly(coord, owner)) {
            bool isBorder = (coord.x < 1 || coord.x > tileMap->rows - 2 || coord.y < 1 || coord.y > tileMap->cols - 2);
            if (!isBorder && tileMap->getTile(coord)->isAccesible) {
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

void Unit::Update(double dt, Vector2 target) {
    if (!currentTile->isUnitOnTile) { // only place that this can be done, in constructor it doesn't change the value for some reason
        currentTile->isUnitOnTile = true;
        currentTile->unitOnTile = this;
    }

    if (canMove) {
        if (!isMoving) {
            if (target.x > gridPosition.x) {
                target.x = gridPosition.x + 1;
                target.y = gridPosition.y;
            } else if (target.x < gridPosition.x) {
                target.x = gridPosition.x - 1;
                target.y = gridPosition.y;
            } else if (target.y > gridPosition.y) {
                target.x = gridPosition.x;
                target.y = gridPosition.y + 1;
            } else if (target.y < gridPosition.y) {
                target.x = gridPosition.x;
                target.y = gridPosition.y - 1;
            }
            setOptions();
            if (tileInOptions(target)) {
                selected = false;
                gridPosition = target;

                currentTile->isUnitOnTile = false;
                currentTile->unitOnTile = NULL;

                newTile = tileMap->getTile(target);
                
                if (newTile->isUnitOnTile) {
                    isFighting = true;
                    newTile->unitOnTile->isFighting = true;
                }

                isMoving = true;
            } else {
                isMoving = false;
            }
            removeOptions();
        } 

        if (isMoving) {
            newPosition = newTile->getPos();
            newPosition = {newPosition.x + 0.35 * tileMap->tileWidth, newPosition.y + 0.1 * tileMap->tileHeight};
            movingProgress += movementSpeed * dt;

            if (isFighting) {
                newTile->isAccesible = false;
                newTile->unitOnTile->canMove = false;
                fight(newTile, dt);
            } else {
                newTile->isUnitOnTile = true;
                newTile->unitOnTile = this;

                currentTile->isUnitOnTile = false;
                currentTile->unitOnTile = NULL;
                newTile->isAccesible = true;
            }

            if ((movingProgress >= 100) && (!isFighting)) {
                currentTile = newTile;
                newTile = NULL;
                newPosition = {0,0};
                isMoving = false;
                movingProgress = 0;
            }
        }
    }

    position = tileMap->gridPosToWorldPos(gridPosition);
    position = {position.x + 0.35 * tileMap->tileWidth, position.y + 0.1 * tileMap->tileHeight};
}

void Unit::Update(double dt)
{
    if (!currentTile->isUnitOnTile) { // only place that this can be done, in constructor it doesn't change the value for some reason
        currentTile->isUnitOnTile = true;
        currentTile->unitOnTile = this;
    }

    if (canMove) {
        if (!isMoving) {
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

                        newTile = tileMap->getTile(tilePos);
                        
                        if (newTile->isUnitOnTile) {
                            isFighting = true;
                            newTile->unitOnTile->isFighting = true;
                        }

                        movingProgress = 0;

                        removeOptions();
                        isMoving = true;
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

        } else {
            newPosition = newTile->getPos();
            newPosition = {newPosition.x + 0.35 * tileMap->tileWidth, newPosition.y + 0.1 * tileMap->tileHeight};
            movingProgress += movementSpeed * dt;

            if (isFighting) {
                newTile->isAccesible = false;
                fight(newTile, dt);
            } else {
                newTile->isUnitOnTile = true;
                newTile->unitOnTile = this;

                currentTile->isUnitOnTile = false;
                currentTile->unitOnTile = NULL;
                newTile->isAccesible = true;
            }

            if ((movingProgress >= 100) && (!isFighting)) {
                currentTile = newTile;
                newTile = NULL;
                newPosition = {0,0};
                isMoving = false;
                movingProgress = 0;
            }
        }
    }

    position = tileMap->gridPosToWorldPos(gridPosition);
    position = {position.x + 0.35 * tileMap->tileWidth, position.y + 0.1 * tileMap->tileHeight};
}

void Unit::Render()
{

    for (int i=0; i < possibleOptions.size(); i++) {
        Tile *tile = tileMap->getTile(possibleOptions.at(i));
        DrawTextureEx(*tileHighLite, tile->getPos(), 0, (double) tileMap->tileHeight / 810, WHITE);
    }

    if (isMoving) {
        if (int(gridPosition.x) % 2 == 0) {
            DrawTextureEx(*texture, {(position.x + newPosition.x)/2, (position.y + newPosition.y)/2}, 0, 0.1, WHITE);
        } else {
            DrawTextureEx(*texture, {(position.x + newPosition.x)/2, (position.y + newPosition.y - tileMap->tileHeight)/2}, 0, 0.1, WHITE);
        }
    } else {
        if (int(gridPosition.x) % 2 == 0) {
            DrawTextureEx(*texture, position, 0, 0.1, WHITE);
        } else {
            DrawTextureEx(*texture, {position.x, position.y - 0.5 * tileMap->tileHeight}, 0, 0.1, WHITE);
        }
    }
}

Unit::Unit(double setMaxHealth, double setDefence, double setMovementSpeed, double setAttackDamage, Map *setTileMap, Camera2D* setCamera, Tile *startTile, Vector2 startingGridPos, std::string setOwner, Texture2D *setTexture, Texture2D *setTileHighLite)
{
    maxHealth = setMaxHealth;
    defence = setMaxHealth;
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
    isFighting = false;
    movingProgress = 0;

    owner = setOwner;

    texture = setTexture;
    tileHighLite = setTileHighLite;
}

Unit::~Unit()
{
    texture = NULL;
    tileHighLite = NULL;
    tileMap = NULL;
    currentTile = NULL;
    camera = NULL;
}
        
