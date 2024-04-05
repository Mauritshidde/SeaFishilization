#include <map>
#include "../raylib.h"


class Overlay
{
private:
    int screenWidth, screenHeight;
    Vector2 inventoryStartPosition;
    int inventoryWidth, inventoryHeight;
    Vector2 buildMenuStartPosition;
    int buildMenuWidth, buildMenuHeight;
    std::map<std::string, Texture2D> tileTextures;
    std::string selectedTile;
public:
    bool isBuildMode;
    void drawBuildMode();
    void drawInventory(int food, int coral);
    bool isMouseOnOverlay();
    Overlay(int screenWidth, int screenHeight);
    ~Overlay();
};

Overlay::Overlay(int screenWidth_ = 1920, int screenHeight_ = 1084) 
{
    screenWidth = screenWidth_;
    screenHeight = screenHeight_;

    inventoryStartPosition = { screenWidth/4*3, 0};
    inventoryWidth = screenWidth/4;
    inventoryHeight = screenHeight/10;

    buildMenuStartPosition = { screenWidth/4, screenHeight/8*7};
    buildMenuWidth = screenWidth/2;
    buildMenuHeight = screenHeight/8;

    isBuildMode = true;
    
    // TODO get sprites as parameter in overlay constructor //
    tileTextures = {
        {"locked", LoadTexture("sprites/resources/BlankTile.png")},
        {"sea", LoadTexture("sprites/resources/BlankTile.png")},
        {"food", LoadTexture("sprites/resources/AlgenTile.png")},
        {"coral", LoadTexture("sprites/resources/CoralTile.png")},
        {"training", LoadTexture("sprites/buildings/TrainingTile.png")},
        {"castleV1", LoadTexture("sprites/castle/CastleTileLVL1.png")},
        {"castleV2", LoadTexture("sprites/castle/CastleTileLVL2.png")},
        {"castleV3", LoadTexture("sprites/castle/CastleTileLVL3.png")},
        {"castleV4", LoadTexture("sprites/castle/CastleTileLVL4.png")},
        {"castleV5", LoadTexture("sprites/castle/CastleTileLVL5.png")}
    };

}

Overlay::~Overlay() 
{    
}

void Overlay::drawBuildMode() 
{
    int imgSize = 100;
    DrawRectangle(buildMenuStartPosition.x, buildMenuStartPosition.y, buildMenuWidth, buildMenuHeight, BROWN);
    Vector2 pos1 = {
        buildMenuStartPosition.x + buildMenuWidth/3 - imgSize/2, 
        buildMenuStartPosition.y + buildMenuHeight/2 - imgSize/2
    };
    Vector2 pos2 = {
        buildMenuStartPosition.x + buildMenuWidth/2 - imgSize/2, 
        buildMenuStartPosition.y + buildMenuHeight/2 - imgSize/2
    };
    Vector2 pos3 = {
        buildMenuStartPosition.x + buildMenuWidth/3 * 2 - imgSize/2, 
        buildMenuStartPosition.y + buildMenuHeight/2 - imgSize/2
    };
    DrawTextureEx(tileTextures["food"], pos1, 0, (double) imgSize / 810, WHITE);
    DrawTextureEx(tileTextures["coral"], pos2, 0, (double) imgSize / 810, WHITE);
    DrawTextureEx(tileTextures["training"], pos3, 0, (double) imgSize / 810, WHITE);
}

void Overlay::drawInventory(int food, int coral) 
{
    DrawRectangle(inventoryStartPosition.x, inventoryStartPosition.y, inventoryWidth, inventoryHeight, BROWN);

    DrawText(TextFormat("Food: %d", food), screenWidth - screenWidth/8, screenHeight/20, 10, WHITE);
    DrawText(TextFormat("Coral: %d", coral), screenWidth - screenWidth/4, screenHeight/20, 10, WHITE);
}

bool Overlay::isMouseOnOverlay() {
    Vector2 mousePos = GetMousePosition();
    bool isXInBuildMenu = (mousePos.x > buildMenuStartPosition.x && mousePos.x < buildMenuStartPosition.x + buildMenuWidth);
    bool isYInBuildMenu = (mousePos.y > buildMenuStartPosition.y && mousePos.y < buildMenuStartPosition.y + buildMenuHeight);
    if(isBuildMode && isXInBuildMenu && isYInBuildMenu) {
        return true;
    }

    bool isXInInventory = (mousePos.x > inventoryStartPosition.x && mousePos.x < inventoryStartPosition.x + inventoryWidth);
    bool isYInInventory = (mousePos.y > inventoryStartPosition.y && mousePos.y < inventoryStartPosition.y + inventoryHeight);
    if (isXInInventory && isYInInventory) {
        return true;
    }
    return false;
}
