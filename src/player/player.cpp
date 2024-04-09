#include <cmath>

#include "player.h"

Player::Player(Vector2 startPosition, int setScreenWidth, int setScreenHeight, Map *setMap, Texture2D *setTileHighLite, std::map<std::string, Texture2D> setUnitTextures)
{
    food = 0;
    coral = 0;

    screenWidth = setScreenWidth;
    screenHeight = setScreenHeight;

    map = setMap;

    unitTextures = setUnitTextures;
    tileHighLite = setTileHighLite;

    position = startPosition;
    camera.target = position;
    camera.rotation = 0.0f;
    camera.zoom = 3.0f;

    playerUnits = UnitInventory("player", map, &camera, setTileHighLite, setUnitTextures);

    castleCost = 50;
    castleLvl = 1;
    castleHealth = 500;

    movementSpeed = 250;
    zoomSpeed = 10;
    mouseMovementSpeed = 100;
    minZoom = 1.2;
    maxZoom = 4;
    maxX = screenWidth;
    minX = 0;
    maxY = screenHeight;
    minY = 0;
    productionSpeed = 10;
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
    } else if (IsKeyDown(KEY_UP)) {
        camera.target.y -= movementSpeed * dt / camera.zoom;
    }
    if (IsKeyDown(KEY_S))
    {
        camera.target.y += movementSpeed * dt / camera.zoom;
    } else if (IsKeyDown(KEY_DOWN)) {
        camera.target.y += movementSpeed * dt / camera.zoom;
    }
    if (IsKeyDown(KEY_A))
    {
        camera.target.x -= movementSpeed * dt / camera.zoom;
    } else if (IsKeyDown(KEY_LEFT)) {
        camera.target.x -= movementSpeed * dt / camera.zoom;
    }
    if (IsKeyDown(KEY_D))
    {
        camera.target.x += movementSpeed * dt / camera.zoom;
    } else if (IsKeyDown(KEY_RIGHT)) {
        camera.target.x += movementSpeed * dt / camera.zoom;
    }

    if (GetMouseWheelMove() > 0) 
    {
        double zoomBefore = camera.zoom;
        camera.zoom += zoomSpeed * dt / camera.zoom;
        if (camera.zoom > maxZoom) {
            camera.zoom = maxZoom;
        }
    }
    else if (GetMouseWheelMove() < 0)
    {
        camera.zoom -= zoomSpeed * dt / camera.zoom;
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
                camera.target.x -= (currentMousePos.x-mouseStartPos.x) * mouseMovementSpeed * dt / camera.zoom;
                camera.target.y -= (currentMousePos.y-mouseStartPos.y) * mouseMovementSpeed * dt / camera.zoom;
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

int Player::getTileCost(std::string type) {
    int tileCount = map->countTilesWithType(type);
    if(tileCount == 0 && type == "coral") return 0; // fist coral is always free
    if(type != "coral") tileCount++;
    int cost = (int) std::pow(1.6, tileCount);
    return cost;
}

bool Player::buyTile(std::string type) {
    int cost = getTileCost(type);
    if (cost > coral) return false;
    
    addCoralAmount(-cost);
    return true;
}

bool Player::buyCastleUpgrade() {
    if (castleLvl > 4) return false;
    if (coral < castleCost) return false;

    castleHealth += 250;
    castleLvl++;
    productionSpeed--;
    addCoralAmount(-castleCost);
    castleCost = castleCost * 2;
    return true;
}

int Player::getCastleLvl() {
    return castleLvl;
}

void Player::Update(double dt, int isBuildMode, bool overlay) {
    playerUnits.Update(dt, overlay);
    movement(dt, isBuildMode);

    if (GetTime() - (int)GetTime() + dt > 1 && (int)GetTime() % productionSpeed == 0) {
        int foodTileCount = map->countTilesWithType("food");
        int coralTileCount = map->countTilesWithType("coral");
        addFoodAmount(foodTileCount); // 1 / tile / prodSpeed
        addCoralAmount(coralTileCount); // 1 / tile / prodSpeed
    }


}

void Player::Render() {
    DrawText(TextFormat("Hp: %d", int(castleHealth)), castlePos.x + 0.5 * map->getTile({0,0})->width, castlePos.y + 0.75 * map->getTile({0,0})->height, 10, WHITE);
    playerUnits.Render();
}

void Player::Start(Vector2 center) {
    camera.offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
    camera.target = map->gridPosToWorldPos(center);
    camera.zoom = 3.0;

    castlePos = map->gridPosToWorldPos(center);
}