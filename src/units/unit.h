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

    bool isMoving;
    bool canMove;

    Texture2D texture;
    Texture2D tileHighLite;
    Map* tileMap;
    Tile* currentTile;
    Camera2D* camera;

    std::vector<Vector2> possibleOptions;

    bool tileInOptions(Vector2 coords);
public:
    bool isAlive;
    bool selected;
    double health;

    Vector2 gridPosition;
    Vector2 position;
    std::string owner;

    void fight(Tile *targetTile, double dt);
    void heal();
    void takeDamage(double damage);
    void move(Vector2 target);
    void moveOneTile(int option);
    bool hasTileEnemy(Vector2 coord, std::string type);
    bool hasTileFriendly(Vector2 coord, std::string type);
    void setOptions();
    void removeOptions();
    
    void Update(double dt);
    void Render();

    Unit(double setMaxHealth=100, double setAttackSpeed=10, double setMovementSpeed=100, double setAttackDamage=100, Map* setTilemap = NULL, Camera2D* setCamera = NULL, Tile *startTile = NULL, Vector2 startingGridPos = {0,0}, std::string setOwner = "enemy");
    ~Unit();
};