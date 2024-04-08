#include "wave.h"

std::vector<Vector2> Wave2::genStartingPositions(int unitAmount) {
    map->getBorders();
    
    for (int i=0; i < unitAmount; i++) {
        
    }
}

void Wave2::spawnWave() {
    int unitAmount = rand() % maxUnitAmount + minUnitAmount;
    int unitLevel = rand() % maxUnitLevel + minUnitLevel;

    genStartingPositions(unitAmount);

    for (int i = 0; i < unitAmount+1; i++) {
        units.createUnit({0,0}, camera, maxUnitAmount);
    }
}

void Wave2::calcWaveLevel() {
    minUnitLevel = round(1 + waveCount/5);
    maxUnitLevel = round(1 + waveCount/2);

    if (minUnitLevel < 1) {
        minUnitLevel = 1;
    } else if (minUnitLevel > 5) {
        minUnitLevel = 5;
    }
    if (maxUnitLevel > 5) {
        maxUnitLevel = 5;
    }

    minUnitAmount = 1 + waveCount/10;
    maxUnitAmount = 2 + waveCount/5;

    if (minUnitAmount < 1) {
        minUnitAmount = 1;
    } else if (minUnitAmount > 20) {
        minUnitAmount = 20;
    }
    if (maxUnitAmount > 25) {
        maxUnitAmount = 25;
    }
}

void Wave2::Update(double dt) {
    // units.UpdateCPU(dt)

    timeUntilNextWave -= dt;

    if (timeUntilNextWave <= 0) {
        timeUntilNextWave = 120;
        spawnWave();
        waveCount++;
    }

    units.Update(dt, {0,0});
}

void Wave2::Render() {
    units.Render();
}

void Wave2::Start() {
    srand (time(NULL)); // set random seed for rand int

    calcWaveLevel();
    units.createUnit({9,9}, camera, 1);
}

Wave2::Wave2(Map *map_, Camera2D *camera_, Texture2D *tileHighLite_, std::map<std::string, Texture2D> unitTextures_)
{
    owner = "Wave";
    map = map_;
    camera = camera_;
    tileHighLite = tileHighLite_;
    unitTextures = unitTextures_;
    waveCount = 0;
    timeUntilNextWave = 120; // in seconds

    units = UnitInventory("wave", map_, camera_, tileHighLite_, unitTextures_);
}


Wave2::~Wave2()
{
}
