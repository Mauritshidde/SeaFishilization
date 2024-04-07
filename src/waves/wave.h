#pragma once
#include <vector>
#include <string>
#include "../raylib.h"

#include "../map/tile.h"
#include "../map/map.h"
#include "../units/unit.h"
#include "unitInventory.h"

class Wave2
{
private:
    UnitInventory units;
    std::string owner;
public:
    void Update(double dt);
    void Render();

    Wave2();
    ~Wave2();
};
