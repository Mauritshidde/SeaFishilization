#include "raylib.h"

class Player
{
private:
    double movementSpeed = 100;
public:
    Camera2D camera = { 0 };
    Vector2 position;
    void movement(double dt);

    Player(Vector2 startPosition={0,0}, int screenWidth=1920, int screenHeight=1084);
    ~Player();
};

Player::Player(Vector2 startPosition, int screenWidth, int screenHeight)
{
    position = startPosition;
    camera.target = position;
    camera.offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
}

Player::~Player()
{

}

void Player::movement(double dt)
{
    if (IsKeyDown(KEY_W))
    {
        camera.target.y -= movementSpeed * dt;
    }
    else if (IsKeyDown(KEY_S))
    {
        camera.target.y += movementSpeed * dt;
    }
    else if (IsKeyDown(KEY_A))
    {
        camera.target.x -= movementSpeed * dt;
    }
    else if (IsKeyDown(KEY_D))
    {
        camera.target.x += movementSpeed * dt;
    }
}