#include "../raylib.h"

class Player
{
private:
    double movementSpeed = 100;
    double zoomSpeed = 10;
    double mouseMovementSpeed = 10;
    Vector2 mouseStartPos;
    
    int screenWidth;
    int screenHeight;

    int food;
    int coral;
public:

    Camera2D camera = { 0 };
    Vector2 position;
    void changeFoodAmount(int amount); // remove food if buying something add food when receiving something
    void changeCoralAmount(int amount); // remove coral if buying something add coral when receiving something
    void movement(double dt);
    int getFoodAmount();
    int getCoralAmount();

    Player(Vector2 startPosition={0,0}, int screenWidth=1920, int screenHeight=1084);
    ~Player();
};

Player::Player(Vector2 startPosition, int setScreenWidth, int setScreenHeight)
{
    food = 0;
    coral = 0;

    screenWidth = setScreenWidth;
    screenHeight = setScreenHeight;
    
    position = startPosition;
    camera.target = position;
    // camera.offset = (Vector2){0,0};
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
    if (IsKeyDown(KEY_S))
    {
        camera.target.y += movementSpeed * dt;
    }
    if (IsKeyDown(KEY_A))
    {
        camera.target.x -= movementSpeed * dt;
    }
    if (IsKeyDown(KEY_D))
    {
        camera.target.x += movementSpeed * dt;
    }

    if (GetMouseWheelMove() > 0) 
    {
        camera.zoom += zoomSpeed * dt;
    }
    else if (GetMouseWheelMove() < 0)
    {
        camera.zoom -= zoomSpeed * dt;
    }


    if (IsMouseButtonPressed(0)) // for camera movement by dragging of the mouse whilst pressing left mouse button
    {
        mouseStartPos = GetMousePosition();
    }

    if (IsMouseButtonDown(0)) 
    {
        Vector2 currentMousePos = GetMousePosition();
        if (currentMousePos.x != mouseStartPos.x || currentMousePos.y != mouseStartPos.y) {
            camera.target.x -= (currentMousePos.x-mouseStartPos.x) * mouseMovementSpeed * dt;
            camera.target.y -= (currentMousePos.y-mouseStartPos.y) * mouseMovementSpeed * dt;
        }
        
        mouseStartPos = GetMousePosition();
    }
}

void Player::changeFoodAmount(int amount) {
    food += amount;
}

void Player::changeCoralAmount(int amount) {
    coral += amount;
}

int Player::getFoodAmount() {
    return food;
}

int Player::getCoralAmount() {
    return coral;
}