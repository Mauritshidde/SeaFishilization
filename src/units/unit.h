#pragma once
#include <cmath>
#include <string>
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
    Texture2D tileHighLite;
    Map* tileMap;
    Tile* currentTile;
    Camera2D* camera;

    std::vector<Vector2> possibleOptions;

    bool tileInOptions(Vector2 coords);
public:
    double selected;
    double health;
    Vector2 gridPosition;
    Vector2 position;
    std::string owner;

    void fight(Tile *targetTile);
    void heal();
    void takeDamage(double damage);
    void move(Vector2 target);
    void moveOneTile(int option);
    bool hasTileEnemy(Vector2 coord);
    bool hasTileFriendly(Vector2 coord);
    void setOptions();
    void removeOptions();
    
    void Update(double dt);
    void Render();

    Unit(double setMaxHealth=100, double setAttackSpeed=10, double setMovementSpeed=100, double setAttackDamage=100, Map* setTilemap = NULL, Camera2D* setCamera = NULL, Tile *startTile = NULL);
    ~Unit();
};