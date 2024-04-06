#include "overlay.h"

Overlay::Overlay(int screenWidth_, int screenHeight_, std::map<std::string, Texture2D> tileTextures_) 
{
    screenWidth = screenWidth_;
    screenHeight = screenHeight_;
    tileTextures = tileTextures_;

    inventoryPos = { screenWidth/4.0f*3.0f, 0};
    inventoryWidth = screenWidth/4.0f;
    inventoryHeight = screenHeight/10.0f;

    buildMenuPos = { screenWidth/4.0f, screenHeight/8.0f*7.0f};
    buildMenuWidth = screenWidth/2.0f;
    buildMenuHeight = screenHeight/8.0f;

    buildTileSize = 120;

    buildTilePositions = {
        {
            buildMenuPos.x + buildMenuWidth/3 - buildTileSize/2, 
            buildMenuPos.y + buildMenuHeight/2 - buildTileSize/2
        },
        {
            buildMenuPos.x + buildMenuWidth/2 - buildTileSize/2, 
            buildMenuPos.y + buildMenuHeight/2 - buildTileSize/2
        },
        {
            buildMenuPos.x + buildMenuWidth/3*2 - buildTileSize/2, 
            buildMenuPos.y + buildMenuHeight/2 - buildTileSize/2
        }
    };
    
    buildTileNames = {
        "food",
        "coral",
        "training"
    };

    selectedBuildTile = -1;
    highlightTileTexture = LoadTexture("sprites/UI-elements/hexHighlight.png");
    
    isBuildMode = true;
}

Overlay::~Overlay() 
{    
}

void Overlay::drawBuildMode() 
{
    DrawRectangle(buildMenuPos.x, buildMenuPos.y, buildMenuWidth, buildMenuHeight, BROWN);
    for(int i = 0; i < buildTilePositions.size(); i++) {
        DrawTextureEx(tileTextures[buildTileNames[i]], buildTilePositions[i], 0, (double) buildTileSize / 810, WHITE);
    }
    if(selectedBuildTile > -1 && selectedBuildTile < buildTilePositions.size()) {
        DrawTextureEx(highlightTileTexture, buildTilePositions[selectedBuildTile], 0, (double) buildTileSize / 810, WHITE);
    }
}

void Overlay::drawInventory(int food, int coral, int score, double time, int wave, double nextWaveTime) 
{
    DrawRectangle(inventoryPos.x, inventoryPos.y, inventoryWidth, inventoryHeight, BROWN);

    DrawText(TextFormat("Food: %d", food), screenWidth - screenWidth/8, screenHeight/30, 10, WHITE);
    DrawText(TextFormat("Coral: %d", coral), screenWidth - screenWidth/4, screenHeight/30, 10, WHITE);
    DrawText(TextFormat("score: %d", score), screenWidth - screenWidth/8, screenHeight/20, 10, WHITE);
    DrawText(TextFormat("time: %d", time), screenWidth - screenWidth/4, screenHeight/20, 10, WHITE);
    DrawText(TextFormat("time until next wave: %d", nextWaveTime), screenWidth - screenWidth/8, screenHeight/15, 10, WHITE);
    DrawText(TextFormat("wave: %d", wave), screenWidth - screenWidth/4, screenHeight/15, 10, WHITE);
}

int Overlay::mouseOnBuildTile() {
    for(int i = 0; i < buildTilePositions.size(); i++) {
        Rectangle buildTileRect = { buildTilePositions[i].x, buildTilePositions[i].y, buildTileSize*1.15f, (float)buildTileSize };
        if (CheckCollisionPointRec(GetMousePosition(), buildTileRect)) {
            return i;
        }
    }
    return -1;
}

void Overlay::selectBuildTile(int buildTile) {
    if(buildTile == selectedBuildTile) {
        selectedBuildTile = -1; // deselct if already selected
        return;
    }
    selectedBuildTile = buildTile;
}

std::string Overlay::getBuildTileName() {
    if(selectedBuildTile < 0 || selectedBuildTile >= buildTileNames.size()) {
        return "";
    }
    return buildTileNames[selectedBuildTile];
}


bool Overlay::isMouseOnOverlay() {
    Vector2 mousePos = GetMousePosition();
    bool isXInBuildMenu = (mousePos.x > buildMenuPos.x && mousePos.x < buildMenuPos.x + buildMenuWidth);
    bool isYInBuildMenu = (mousePos.y > buildMenuPos.y && mousePos.y < buildMenuPos.y + buildMenuHeight);
    if(isBuildMode && isXInBuildMenu && isYInBuildMenu) {
        return true;
    }

    bool isXInInventory = (mousePos.x > inventoryPos.x && mousePos.x < inventoryPos.x + inventoryWidth);
    bool isYInInventory = (mousePos.y > inventoryPos.y && mousePos.y < inventoryPos.y + inventoryHeight);
    if (isXInInventory && isYInInventory) {
        return true;
    }
    return false;
}
