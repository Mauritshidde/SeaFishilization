#include "wave.h"

std::vector<Vector2> Wave2::genStartingPositions(int unitAmount) {
    std::vector<Vector2> borders = map->getBorders();

    std::vector<int> numbers;
    
    int times = 0;
    while (numbers.size() < unitAmount || times >= 100) {
        int number = rand() % borders.size();

        numbers.push_back(number);

        for (int i=0; i < numbers.size()-1; i++) {
            if (numbers.at(i) == number) {
                numbers.pop_back();
                break;
            }
        }

        times++;
    }

    std::vector<Vector2> positions;

    for (int i=0; i < numbers.size(); i++) {
        positions.push_back(borders.at(numbers.at(i)));
    }

    return positions;
}

void Wave2::spawnWave() {
    int unitAmountDifference = maxUnitAmount - minUnitAmount;
    int unitLevelDifference = maxUnitLevel-minUnitLevel;

    int unitAmount;
    if (unitLevelDifference > 0) {
        unitAmount = rand() % unitAmountDifference;
    } else {
        unitAmount = 0;
    }

    int unitLevel;
    if (unitLevelDifference > 0) {
        unitLevel = rand() % unitLevelDifference;
    } else {
        unitLevel = 0;
    }

    if (statMultiplier > 2) {
        statMultiplier = 2;
    }

    unitAmount += minUnitAmount;
    unitLevel += minUnitLevel;

    std::vector<Vector2> startingPositions = genStartingPositions(unitAmount);

    for (int i=0; i < startingPositions.size(); i++) {
        units.createUnit(startingPositions.at(i), camera, unitLevel, statMultiplier);
    }
}

void Wave2::calcWaveLevel() {
    minUnitLevel = round(1 + waveCount/5);
    maxUnitLevel = round(1 + waveCount/2);

    if (minUnitLevel < 1) {
        minUnitLevel = 1;
    } else if (minUnitLevel > 5) {
        minUnitLevel = 5;
        statMultiplier += 0.05;
    }
    if (maxUnitLevel > 5) {
        maxUnitLevel = 5;
        statMultiplier += 0.02;
    }

    minUnitAmount = 1 + waveCount/10;
    maxUnitAmount = 2 + waveCount/5;

    if (minUnitAmount < 1) {
        minUnitAmount = 1;
    } else if (minUnitAmount > 20) {
        minUnitAmount = 20;
        statMultiplier += 0.02;
    }
    if (maxUnitAmount > 25) {
        statMultiplier += 0.03;
        maxUnitAmount = 25;
    }

    waveCoolDown -= 0.5;

    if (waveCoolDown < 10) {
        waveCoolDown = 10;
    }
}

void Wave2::Update(double dt) {
    // units.UpdateCPU(dt)

    timeUntilNextWave -= dt;

    if (timeUntilNextWave <= 0) {
        timeUntilNextWave = 45;
        spawnWave();
        waveCount++;
        calcWaveLevel();
    }

    units.Update(dt, target);
}

void Wave2::Render() {
    units.Render();
}

void Wave2::Start() {
    srand (time(NULL)); // set random seed for rand int

    target = {map->rows/2, map->cols/2};

    calcWaveLevel();
}

Wave2::Wave2(Map *map_, Camera2D *camera_, Texture2D *tileHighLite_, std::map<std::string, Texture2D> unitTextures_)
{
    owner = "Wave";
    map = map_;
    camera = camera_;
    tileHighLite = tileHighLite_;
    unitTextures = unitTextures_;
    waveCount = 0;
    waveCoolDown = 50;
    timeUntilNextWave = 60; // in seconds
    statMultiplier = 1;

    units = UnitInventory("wave", map_, camera_, tileHighLite_, unitTextures_);
}


Wave2::~Wave2()
{
}
