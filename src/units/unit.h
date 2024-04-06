#pragma once
#include "../raylib.h"

#include "../map/tile.h"
#include "../map/map.h"

class Unit
{
private:
    double maxHealth;
    double attackSpeed;
    double movementSpeed;
    double attackDamage;

    Texture2D texture;
    Map* tileMap;
    Tile* currentTile;
public:
    double selected;
    double health;
    Vector2 gridPosition;
    Vector2 position;

    void fight(Tile *targetTile);
    void heal();
    void takeDamage(double damage);
    void move(Vector2 target);
    void moveOneTile(int option);

    void Update(double dt);
    void Render();

    Unit(double setMaxHealth=100, double setAttackSpeed=10, double setMovementSpeed=100, double setAttackDamage=100, Map* setTilemap = NULL);
    ~Unit();
};