#include <map>
#include "../raylib.h"


class Overlay
{
private:
    int screenWidth;
    int screenHeight;
    std::map<std::string, Texture2D> tileTextures;
public:
    void drawBuildMode();
    void drawInventory(int food, int coral);
    Overlay(int screenWidth, int screenHeight);
    ~Overlay();
};

Overlay::Overlay(int screenWidth_ = 1920, int screenHeight_ = 1084) 
{
    screenWidth = screenWidth_;
    screenHeight = screenHeight_;
    
    // TODO get sprites as parameter in overlay constructor //
    tileTextures = {
        {"locked", LoadTexture("sprites/resources/BlankTile.png")},
        {"sea", LoadTexture("sprites/resources/BlankTile.png")},
        {"food", LoadTexture("sprites/resources/AlgenTile.png")},
        {"coral", LoadTexture("sprites/resources/CoralTile.png")},
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
    int imgSize = 51;
    int x = screenWidth / 4;
    int y = screenHeight / 8 * 7;
    int w = screenWidth / 2;
    int h = screenHeight / 8;
    DrawRectangle(x, y, w, h, BROWN);
    Vector2 pos1 = {
        x + w/3 - imgSize, 
        y + h/2 - imgSize
    };
    Vector2 pos2 = {
        x + w/2 - imgSize, 
        y + h/2 - imgSize
    };
    Vector2 pos3 = {
        x + w/3 * 2 - imgSize, 
        y + h/2 - imgSize
    };
    DrawTextureEx(tileTextures["food"], pos1, 0, 0.1, WHITE);
    DrawTextureEx(tileTextures["coral"], pos2, 0, 0.1, WHITE);
    DrawTextureEx(tileTextures["sea"], pos3, 0, 0.1, WHITE);
}

void Overlay::drawInventory(int food, int coral) 
{
    DrawRectangle(screenWidth - screenWidth/4, 0, screenWidth/4, screenHeight/10, BLACK);

    DrawText(TextFormat("Food: %d", food), screenWidth - screenWidth/8, screenHeight/20, 10, WHITE);
    DrawText(TextFormat("Coral: %d", coral), screenWidth - screenWidth/4, screenHeight/20, 10, WHITE);
}