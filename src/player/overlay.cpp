#include <iostream>
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

    coralTileCost = 0;
    foodTileCost = 0;
    trainingTileCost = 0;

    selectedBuildTile = -1;
    highlightTileTexture = LoadTexture("sprites/UI-elements/hexHighlight.png");

    castleLvl = 1;
    castleHp = 5;
    
    isBuildMode = true;
}

Overlay::~Overlay() 
{    
}

void Overlay::drawBuildMode() 
{
    Font font = GetFontDefault();
    // const char *text = TextFormat("cost: %d", coralTileCost);
    float fontSize = 18;
    float spacing = 5;

    // Vector2 textDimentions = MeasureTextEx(font, text, fontSize, spacing);

    DrawRectangle(buildMenuPos.x, buildMenuPos.y, buildMenuWidth, buildMenuHeight, BROWN);

    for(int i = 0; i < buildTilePositions.size(); i++) {
        DrawTextureEx(tileTextures[buildTileNames[i]], buildTilePositions[i], 0, (double) buildTileSize / 810, WHITE);
    }

    const char*text0 = TextFormat("%d coral", foodTileCost);
    Vector2 textDimentions0 = MeasureTextEx(font, text0, fontSize, spacing);
    Vector2 position0 = {
        buildTilePositions[0].x + buildTileSize*1.15f / 2 - textDimentions0.x / 2, 
        buildTilePositions[0].y + buildTileSize / 2
    };
    DrawTextEx(font, "cost:", (Vector2){position0.x + fontSize, position0.y - fontSize}, fontSize * 0.8f, spacing, WHITE);
    DrawTextEx(font, text0, position0, fontSize, spacing, WHITE);
    
    const char*text1 = TextFormat("%d coral", coralTileCost);
    Vector2 textDimentions1 = MeasureTextEx(font, text1, fontSize, spacing);
    Vector2 position1 = {
        buildTilePositions[1].x + buildTileSize*1.15f / 2 - textDimentions1.x / 2, 
        buildTilePositions[1].y + buildTileSize / 2
    };
    DrawTextEx(font, "cost:", (Vector2){position1.x + fontSize, position1.y - fontSize}, fontSize * 0.8f, spacing, WHITE);
    DrawTextEx(font, text1, position1, fontSize, spacing, WHITE);
    
    const char*text2 = TextFormat("%d coral", trainingTileCost);
    Vector2 textDimentions2 = MeasureTextEx(font, text2, fontSize, spacing);
    Vector2 position2 = {
        buildTilePositions[2].x + buildTileSize*1.15f / 2 - textDimentions2.x / 2, 
        buildTilePositions[2].y + buildTileSize / 2
    };
    DrawTextEx(font, "cost:", (Vector2){position2.x + fontSize / 2, position2.y - fontSize}, fontSize * 0.8f, spacing, DARKGRAY);
    DrawTextEx(font, text2, position2, fontSize, spacing, DARKGRAY);

    if(selectedBuildTile > -1 && selectedBuildTile < buildTilePositions.size()) {
        DrawTextureEx(highlightTileTexture, buildTilePositions[selectedBuildTile], 0, (double) buildTileSize / 810, WHITE);
    }

}

void Overlay::drawInventory(int food, int coral, int score, int time, int wave, int nextWaveTime) 
{
    DrawRectangle(inventoryPos.x, inventoryPos.y, inventoryWidth, inventoryHeight, BROWN);

    DrawText(TextFormat("Food: %d", food), screenWidth - screenWidth/8, screenHeight/30, 10, WHITE);
    DrawText(TextFormat("Coral: %d", coral), screenWidth - screenWidth/4, screenHeight/30, 10, WHITE);
    DrawText(TextFormat("score: %d", score), screenWidth - screenWidth/8, screenHeight/20, 10, WHITE);
    DrawText(TextFormat("time: %d", time), screenWidth - screenWidth/4, screenHeight/20, 10, WHITE);
    DrawText(TextFormat("time until next wave: %d", nextWaveTime), screenWidth - screenWidth/8, screenHeight/15, 10, WHITE);
    DrawText(TextFormat("wave: %d", wave), screenWidth - screenWidth/4, screenHeight/15, 10, WHITE);
}

void Overlay::drawCastleMenu() 
{
    int level = 1;
    int fontSize = 50;
    Vector2 startPosition = { screenWidth / 3, screenHeight / 2 - fontSize * 5 };
    Rectangle rect = { startPosition.x, startPosition.y, screenWidth / 3, fontSize * 10 };
    DrawRectangleRounded(rect, 0.2f, 0.0f, WHITE);
    DrawText("UPGRADE CASTLE", startPosition.x + fontSize, startPosition.y + fontSize, fontSize, DARKGRAY);
    DrawText("×", startPosition.x + fontSize * 13.5, startPosition.y + fontSize * 0.9, fontSize, DARKGRAY);
    DrawText(TextFormat("TO LEVEL %d", level), startPosition.x + fontSize, startPosition.y + fontSize * 2.5, fontSize / 2, DARKGRAY);
    DrawText("- Unlock new fish!", startPosition.x + fontSize, startPosition.y + fontSize * 4, fontSize / 2, GOLD);
    DrawText(TextFormat("- Production time to %d sec (-1 sec)", 5 - 1), startPosition.x + fontSize, startPosition.y + fontSize * 5, fontSize / 2, GOLD);
    DrawText(TextFormat("- Castle protection to %d hp (+5 hp)", 5), startPosition.x + fontSize, startPosition.y + fontSize * 6, fontSize / 2, GOLD);
    Rectangle buyRect = { startPosition.x + fontSize, startPosition.y + fontSize * 7.5, fontSize * 4, fontSize * 1.5 };
    DrawRectangleRounded(buyRect, 0.2f, 0.0f, DARKGREEN);
    DrawText("LEVEL UP!", startPosition.x + fontSize * 1.75, startPosition.y + fontSize * 8, fontSize / 2, WHITE);
}

int Overlay::mouseOnBuildTile() 
{
    for(int i = 0; i < buildTilePositions.size(); i++) {
        Rectangle buildTileRect = { buildTilePositions[i].x, buildTilePositions[i].y, buildTileSize*1.15f, (float)buildTileSize };
        if (CheckCollisionPointRec(GetMousePosition(), buildTileRect)) {
            return i;
        }
    }
    return -1;
}

void Overlay::selectBuildTile(int buildTile) 
{
    if(buildTile == selectedBuildTile) {
        selectedBuildTile = -1; // deselct if already selected
        return;
    }
    selectedBuildTile = buildTile;
}

std::string Overlay::getBuildTileName() 
{
    if(selectedBuildTile < 0 || selectedBuildTile >= buildTileNames.size()) {
        return "";
    }
    return buildTileNames[selectedBuildTile];
}


bool Overlay::isMouseOnOverlay() 
{
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

void Overlay::setTileTypeCosts(int foodCost, int coralCost, int trainingCost)
{
    foodTileCost = foodCost;
    coralTileCost = coralCost;
    trainingTileCost = trainingCost;
}