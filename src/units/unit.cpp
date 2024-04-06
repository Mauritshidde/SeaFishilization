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

    // if (movingDone) {
        switch (option)
        {
        case 0: // move up
            position.y -= 1;
            break;
        case 1: // move right up
            position.x += 1;
            position.y -= 1;
            break;
        case 2: // move right down
            position.x += 1;
            position.y += 1;
            break;
        case 3: // move down
            position.y += 1;
            break;
        case 4: // move left down
            position.x -= 1;
            position.y += 1;
            break;
        case 5: // move left up
            position.x -= 1;
            position.y -= 1;
            break;

        default:
            break;
        }
        // movingDone = false;
        // movingProgress = 0;
        // unitMoving = false;
    // }
}

void Unit::move(Vector2 target) // target is given in hexagon coords
{
    Tile *targetTile = tileMap->getTile(target);

    if (!targetTile->isUnitOnTile) {
        position = target;
        currentTile->isUnitOnTile = false;
        currentTile->unitOnTile = NULL;

        targetTile->unitOnTile = this;
        targetTile->isUnitOnTile = true;
    } else {
        fight(targetTile);
    }


    bool unitMoving = false;

    if (unitMoving) {
        // pathfinding

        moveOneTile(1);
    }

}

void Unit::Update(double dt)
{

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
    DrawTextureEx(texture, position, 0, 0.1, WHITE);
}

Unit::Unit(double setMaxHealth, double setAttackSpeed, double setMovementSpeed, double setAttackDamage, Map *setTileMap)
{
    maxHealth = setMaxHealth;
    attackSpeed = setMaxHealth;
    movementSpeed = setMovementSpeed;
    attackDamage = setAttackDamage;

    selected = false;
    health = setMaxHealth;
    gridPosition = {10,10};

    tileMap = setTileMap;

    texture = LoadTexture("sprites/units/melee/Battlefish.png");
}

Unit::~Unit()
{
    // delete tileMap;
    // delete currentTile;

    // tileMap = NULL;
    // currentTile = NULL;
}
