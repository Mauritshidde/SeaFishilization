#include <map>
#include "../raylib.h"


class Overlay
{
private:
    int screenWidth, screenHeight;
    Vector2 inventoryPos;
    int inventoryWidth, inventoryHeight;
    Vector2 buildMenuPos;
    int buildMenuWidth, buildMenuHeight;
    Vector2 buildTilePos0, buildTilePos1, buildTilePos2;
    std::vector<Vector2> buildTilePositions;
    int buildTileSize;
    int selectedBuildTile;
    Texture2D highlightTileTexture;

    std::map<std::string, Texture2D> tileTextures;
public:
    bool isBuildMode;
    void drawBuildMode();
    void drawInventory(int food, int coral);
    bool isMouseOnOverlay();
    int mouseOnBuildTile();
    void selectBuildTile(int buildTile);
    Overlay(int screenWidth, int screenHeight);
    ~Overlay();
};

Overlay::Overlay(int screenWidth_ = 1920, int screenHeight_ = 1084) 
{
    screenWidth = screenWidth_;
    screenHeight = screenHeight_;

    inventoryPos = { screenWidth/4*3, 0};
    inventoryWidth = screenWidth/4;
    inventoryHeight = screenHeight/10;

    buildMenuPos = { screenWidth/4, screenHeight/8*7};
    buildMenuWidth = screenWidth/2;
    buildMenuHeight = screenHeight/8;

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

    selectedBuildTile = -1;
    highlightTileTexture = LoadTexture("sprites/UI-elements/hexHighlight.png");
    
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

    isBuildMode = true;
}

Overlay::~Overlay() 
{    
}

void Overlay::drawBuildMode() 
{
    DrawRectangle(buildMenuPos.x, buildMenuPos.y, buildMenuWidth, buildMenuHeight, BROWN);
    DrawTextureEx(tileTextures["food"], buildTilePositions[0], 0, (double) buildTileSize / 810, WHITE);
    DrawTextureEx(tileTextures["coral"], buildTilePositions[1], 0, (double) buildTileSize / 810, WHITE);
    DrawTextureEx(tileTextures["training"], buildTilePositions[2], 0, (double) buildTileSize / 810, WHITE);
    if(selectedBuildTile > -1 && selectedBuildTile < buildTilePositions.size()) {
        DrawTextureEx(highlightTileTexture, buildTilePositions[selectedBuildTile], 0, (double) buildTileSize / 810, WHITE);
    }
}

void Overlay::drawInventory(int food, int coral) 
{
    DrawRectangle(inventoryPos.x, inventoryPos.y, inventoryWidth, inventoryHeight, BROWN);

    DrawText(TextFormat("Food: %d", food), screenWidth - screenWidth/8, screenHeight/20, 10, WHITE);
    DrawText(TextFormat("Coral: %d", coral), screenWidth - screenWidth/4, screenHeight/20, 10, WHITE);
}

int Overlay::mouseOnBuildTile() {
    Rectangle buildTileRect0 = { buildTilePositions[0].x, buildTilePositions[0].y, buildTileSize*1.15, buildTileSize };
    Rectangle buildTileRect1 = { buildTilePositions[1].x, buildTilePositions[1].y, buildTileSize*1.15, buildTileSize };
    Rectangle buildTileRect2 = { buildTilePositions[2].x, buildTilePositions[2].y, buildTileSize*1.15, buildTileSize };

    if (CheckCollisionPointRec(GetMousePosition(), buildTileRect0)) {
        return 0;
    } else if (CheckCollisionPointRec(GetMousePosition(), buildTileRect1)) {
        return 1;
    } else if (CheckCollisionPointRec(GetMousePosition(), buildTileRect2)) {
        return 2;
    }
    return -1;
}

void Overlay::selectBuildTile(int buildTile) {
    selectedBuildTile = buildTile;
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
