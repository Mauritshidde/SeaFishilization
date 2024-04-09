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

    trainingCooldown = 0.0;

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

void Overlay::drawCastleMenu(int level) 
{
    int cost = 25 * std::pow(2, level);
    int productionSpeed = 10 - level;
    int hp = (level + 1) * 250;
    int fontSize = 50;
    Vector2 startPosition = { screenWidth / 10 * 3, screenHeight / 2 - fontSize * 5 };
    Rectangle rect = { startPosition.x, startPosition.y, screenWidth / 2.5, fontSize * 10 };
    DrawRectangleRounded(rect, 0.2f, 0.0f, WHITE);
    DrawText(TextFormat("UPGRADE CASTLE TO LVL %d", level), startPosition.x + fontSize, startPosition.y + fontSize, fontSize, DARKGRAY);
    if(level >= 5) {
        DrawText("MAX LVL REACHED!", startPosition.x + fontSize, startPosition.y + fontSize * 2.5, fontSize / 2, RED);
        Rectangle cancelRect = { startPosition.x + fontSize * 7, startPosition.y + fontSize * 8, fontSize * 5, fontSize * 1.5 };
        DrawRectangleRounded(cancelRect, 0.2f, 0.0f, RED);
        DrawText("[C] CANCEL", startPosition.x + fontSize * 8.25, startPosition.y + fontSize * 8.5, fontSize / 2, WHITE);
        return;
    }

    // ? upgrade information ? //
    // DrawText("×", startPosition.x + fontSize * 13.5, startPosition.y + fontSize * 0.9, fontSize, DARKGRAY);
    DrawText(TextFormat("BUILD COST %d CORAL", cost), startPosition.x + fontSize, startPosition.y + fontSize * 2.5, fontSize / 2, RED);
    DrawText("- Unlock new fish!", startPosition.x + fontSize, startPosition.y + fontSize * 4, fontSize / 2, GOLD);
    DrawText(TextFormat("- Production time to %d sec (-1 sec)", productionSpeed), startPosition.x + fontSize, startPosition.y + fontSize * 5, fontSize / 2, GOLD);
    DrawText(TextFormat("- Castle protection to %d hp (+250 hp)", hp), startPosition.x + fontSize, startPosition.y + fontSize * 6, fontSize / 2, GOLD);
    
    // ? BUY button ? //
    Rectangle buyRect = { startPosition.x + fontSize, startPosition.y + fontSize * 8, fontSize * 5, fontSize * 1.5 };
    DrawText("press key:", startPosition.x + fontSize, startPosition.y + fontSize * 7, fontSize / 2, DARKGRAY);
    DrawRectangleRounded(buyRect, 0.2f, 0.0f, DARKGREEN);
    DrawText("[L] LEVEL UP!", startPosition.x + fontSize * 1.75, startPosition.y + fontSize * 8.5, fontSize / 2, WHITE);

    // ? CANCEL button ? //
    Rectangle cancelRect = { startPosition.x + fontSize * 7, startPosition.y + fontSize * 8, fontSize * 5, fontSize * 1.5 };
    DrawRectangleRounded(cancelRect, 0.2f, 0.0f, RED);
    DrawText("[C] CANCEL", startPosition.x + fontSize * 8.25, startPosition.y + fontSize * 8.5, fontSize / 2, WHITE);
}

void Overlay::drawTrainingMenu(int level) 
{
    std::cout << trainingCooldown << std::endl;
    int fontSize = 50;
    Vector2 startPosition = { screenWidth / 10 * 2, screenHeight / 2 - fontSize * 7.5 };
    Rectangle rect = { startPosition.x, startPosition.y, screenWidth / 10 * 6, fontSize * 15 };
    DrawRectangleRounded(rect, 0.2f, 0.0f, WHITE);
    DrawText("FISH TRAINING AREA!", startPosition.x + fontSize, startPosition.y + fontSize, fontSize, DARKGRAY);
    
    // ? CANCEL button ? //
    Rectangle cancelRect = { startPosition.x + fontSize, startPosition.y + fontSize * 12.5, fontSize * 5, fontSize * 1.5 };
    DrawRectangleRounded(cancelRect, 0.2f, 0.0f, RED);
    DrawText("[C] CANCEL", startPosition.x + fontSize * 1.75, startPosition.y + fontSize * 13, fontSize / 2, WHITE);
    
    if(trainingCooldown > 0.0f) {
        DrawText(TextFormat("COOLDOWN: %d seconds", (int)trainingCooldown), startPosition.x + fontSize * 1.75, startPosition.y + fontSize * 3, fontSize / 3 * 2, RED);
        return;
    }
    
    // ? BUY button 1-5 ? //
    for(int i = 1; i < 6; i++) {

        int cost, maxHealth, damage, movementSpeed, defence;
        switch (i)
        {
        case 1:
            cost = 10;
            maxHealth = 100;
            damage = 10;
            movementSpeed = 30;
            defence = 5;
            break;
        case 2:
            cost = 20;
            maxHealth = 220;
            damage = 20;
            movementSpeed = 60;
            defence = 7;
            break;
        case 3:
            cost = 40;
            maxHealth = 450;
            damage = 34;
            movementSpeed = 30;
            defence = 15;
            break;
        case 4:
            cost = 80;
            maxHealth = 854;
            damage = 50;
            movementSpeed = 30;
            defence = 19;
            break;
        case 5:
            cost = 160;
            maxHealth = 1200;
            damage = 120;
            movementSpeed = 20;
            defence = 25;
            break;
        default:
            break;
        }

        Color color = DARKGREEN;
        if(i > level) {
            color = DARKGRAY;
        }
        Rectangle buyRect = { startPosition.x + fontSize, startPosition.y + fontSize * (0.5 + 2 * i), fontSize * 5, fontSize * 1.5 };
        DrawRectangleRounded(buyRect, 0.2f, 0.0f, color);
        DrawText(TextFormat("[%d] BUY LVL %d", i, i), startPosition.x + fontSize * 1.75, startPosition.y + fontSize * (1 + 2 * i), fontSize / 2, WHITE);
        
        const char *text = TextFormat("cost: %d - hp: %d - damage: %d - move speed: %d - defence: %d", cost, maxHealth, damage, movementSpeed, defence);
        DrawText(text, startPosition.x + fontSize * 6.75, startPosition.y + fontSize * (1 + 2 * i), fontSize / 2, DARKGRAY);
    }

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

void Overlay::updateCooldown(double dt)
{
    if(trainingCooldown > 0.0) {
        trainingCooldown -= dt;
    }
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