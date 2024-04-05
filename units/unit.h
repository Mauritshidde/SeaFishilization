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
    Vector2 position;

    void heal();
    void takeDamage();
    void move(Vector2 target);
    void moveOneTile(int option);

    void Update();
    void Render();

    Unit(double setMaxHealth, double setAttackSpeed, double setMovementSpeed, double setAttackDamage);
    ~Unit();
};

void Unit::heal() {

}

void Unit::takeDamage() 
{

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

Unit::Unit(double setMaxHealth, double setAttackSpeed, double setMovementSpeed, double setAttackDamage)
{
    maxHealth = setMaxHealth;
    attackSpeed = setMaxHealth;
    movementSpeed = setMovementSpeed;
    attackDamage = setAttackDamage;

    selected = false;
    health = setMaxHealth;

    texture = LoadTexture("sprites/units/melee/Battlefish.png");
}

Unit::~Unit()
{
}
