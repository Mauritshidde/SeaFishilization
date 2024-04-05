#pragma once
#include <map>
#include <vector>
#include <string>
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
    std::vector<std::string> buildTileNames;
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
    std::string getBuildTileName();
    Overlay(int screenWidth = 1920, int screenHeight = 1084, std::map<std::string, Texture2D> tileTextures_ = std::map<std::string, Texture2D>());
    ~Overlay();
};