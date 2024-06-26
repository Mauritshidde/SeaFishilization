#pragma once
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <cmath>
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
    
    int foodTileCost, coralTileCost, trainingTileCost;

    
    std::vector<std::string> buildTileNames;
    Texture2D highlightTileTexture;

    std::map<std::string, Texture2D> tileTextures;
public:
    double trainingCooldown;
    int selectedBuildTile;
    bool isBuildMode;
    void drawBuildMode();
    void drawInventory(int food, int coral, int score, int time, int wave, int nextWaveTime);
    void drawCastleMenu(int level);
    void drawTrainingMenu(int level);
    bool isMouseOnOverlay();
    int mouseOnBuildTile();
    void selectBuildTile(int buildTile);
    std::string getBuildTileName();
    void setTileTypeCosts(int foodCost, int coralCost, int trainingCost);
    void updateCooldown(double dt);
    Overlay(int screenWidth = 1920, int screenHeight = 1084, std::map<std::string, Texture2D> tileTextures_ = std::map<std::string, Texture2D>());
    ~Overlay();
};