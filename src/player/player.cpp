#include <cmath>

#include "player.h"

Player::Player(Vector2 startPosition, int setScreenWidth, int setScreenHeight, Map *setMap, Texture2D *setTileHighLite, std::map<std::string, Texture2D> setUnitTextures)
{
    food = 0;
    coral = 6;

    screenWidth = setScreenWidth;
    screenHeight = setScreenHeight;

    map = setMap;

    unitTextures = setUnitTextures;
    tileHighLite = setTileHighLite;

    position = startPosition;
    camera.target = position;
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    playerUnits = UnitInventory("player", map, &camera, setTileHighLite, setUnitTextures);
    // std::cout << "jes" << std::endl;

    movementSpeed = 250;
    zoomSpeed = 10;
    mouseMovementSpeed = 100;
    minZoom = 0.3;
    maxZoom = 3;
    maxX = screenWidth;
    minX = 0;
    maxY = screenHeight;
    minY = 0;
}

Player::~Player()
{
    map = NULL;
}

void Player::movement(double dt, int isBuildMode)
{
    if (IsKeyDown(KEY_W))
    {
        camera.target.y -= movementSpeed * dt / camera.zoom;
    }
    if (IsKeyDown(KEY_S))
    {
        camera.target.y += movementSpeed * dt / camera.zoom;
    }
    if (IsKeyDown(KEY_A))
    {
        camera.target.x -= movementSpeed * dt / camera.zoom;
    }
    if (IsKeyDown(KEY_D))
    {
        camera.target.x += movementSpeed * dt / camera.zoom;
    }

    if (GetMouseWheelMove() > 0) 
    {
        camera.zoom += zoomSpeed * dt;
        if (camera.zoom > maxZoom) {
            camera.zoom = maxZoom;
        }
    }
    else if (GetMouseWheelMove() < 0)
    {
        camera.zoom -= zoomSpeed * dt;
        if (camera.zoom < minZoom) {
            camera.zoom = minZoom;
        }
    }


    if (isBuildMode == -1) {
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
}

void Player::addFoodAmount(int amount) {
    food += amount;
}

void Player::addCoralAmount(int amount) {
    coral += amount;
}

int Player::getFoodAmount() {
    return food;
}

int Player::getCoralAmount() {
    return coral;
}

bool Player::buyTile(std::string type) {
    int tileCount = map->countTilesWithType(type);
    int cost = (tileCount + 1) * 2;

    if (cost > coral) return false;
    
    addCoralAmount(-cost);
    return true;
}

void Player::Update(double dt, int isBuildMode) {
    playerUnits.Update(dt);
    movement(dt, isBuildMode);

    if (GetTime() - static_cast<int>(GetTime()) + dt > 1) {
        int foodTileCount = map->countTilesWithType("food");
        int coralTileCount = map->countTilesWithType("coral");
        addFoodAmount(foodTileCount); // 1 / tile / sec
        addCoralAmount(coralTileCount); // 1 / tile / sec
    }


}

void Player::Render() {
    playerUnits.Render();
}

void Player::Start() {
    playerUnits.createUnit(100, 10, 100, {10, 10}, &camera);
    playerUnits.createUnit(100, 10, 100, {11, 10}, &camera);
    playerUnits.createUnit(100, 10, 100, {12, 10}, &camera);
}