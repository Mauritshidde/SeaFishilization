#pragma once
#include "../raylib.h"

class Unit
{
private:
    double maxHealth;
    double attackSpeed;
    double movementSpeed;
    double attackDamage;

    Texture2D texture;
public:
    double selected;
    double health;
    Vector2 gridPosition;
    Vector2 position;

    void heal();
    void takeDamage(double damage);
    void move(Vector2 target);
    void moveOneTile(int option);

    void Update(double dt);
    void Render();

    Unit(double setMaxHealth=100, double setAttackSpeed=10, double setMovementSpeed=100, double setAttackDamage=100);
    ~Unit();
};