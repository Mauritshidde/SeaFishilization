#include "../raylib.h"

class Unit
{
private:
    double maxHealth;
    double attackSpeed;
    double movementSpeed;
    double attackDamage;

public:
    double selected;
    double health;
    Vector2 position;

    void heal();
    void takeDamage();
    void move();


    Unit(double setMaxHealth, double setAttackSpeed, double setMovementSpeed, double setAttackDamage);
    ~Unit();
};

void Unit::move(Vector2 target) 
{
    
}

void Unit::takeDamage() 
{

}

void Unit::move()
{

}

Unit::Unit(double setMaxHealth, double setAttackSpeed, double setMovementSpeed, double setAttackDamage)
{
    maxHealth = setMaxHealth;
    attackSpeed = setMaxHealth;
    movementSpeed = setMovementSpeed;
    attackDamage = setAttackDamage;

    selected = false;
    health = setMaxHealth;
}

Unit::~Unit()
{
}
