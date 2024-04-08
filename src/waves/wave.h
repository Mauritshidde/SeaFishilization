#pragma once
#include <vector>
#include <string>
#include <cmath>
#include <random>
#include "../raylib.h"

#include "../units/unitInventory.h"
#include "../map/tile.h"
#include "../map/map.h"
#include "../units/unit.h"

class Wave2
{
private:
    UnitInventory units;
    std::string owner;

    Map *map;
    Camera2D *camera;
    Texture2D *tileHighLite;
    std::map<std::string, Texture2D> unitTextures;
    Vector2 target;

    int maxUnitLevel;
    int minUnitLevel;

    int minUnitAmount;
    int maxUnitAmount;

    std::vector<Vector2> genStartingPositions(int unitAmount);
    void spawnWave();
    void calcWaveLevel();
public:
    int waveCount;
    double timeUntilNextWave;
    
    void Update(double dt);
    void Render();
    void Start();

    Wave2(Map *map_ = NULL, Camera2D *camera_ = NULL, Texture2D *tileHighLite_ = NULL, std::map<std::string, Texture2D> unitTextures_ = {});
    ~Wave2();
};
