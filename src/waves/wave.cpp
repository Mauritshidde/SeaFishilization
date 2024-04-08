#include "wave.h"

void Wave2::Update(double dt) {
    // units.UpdateCPU(dt)
    units.Update(dt, {0,0});
}

void Wave2::Render() {
    units.Render();
}

void Wave2::Start() {
    units.createUnit(100, 10, 100, {9,9}, camera);
}

Wave2::Wave2(Map *map_, Camera2D *camera_, Texture2D *tileHighLite_, std::map<std::string, Texture2D> unitTextures_)
{
    owner = "Wave";
    map = map_;
    camera = camera_;
    tileHighLite = tileHighLite_;
    unitTextures = unitTextures_;

    units = UnitInventory("wave", map_, camera_, tileHighLite_, unitTextures_);
}


Wave2::~Wave2()
{
}
