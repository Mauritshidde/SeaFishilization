#include "wave.h"

void Wave2::Update(double dt) {
    // units.UpdateCPU(dt)
}

void Wave2::Render() {
    units.Render();
}

Wave2::Wave2()
{
    owner = "Wave2";
}

Wave2::~Wave2()
{
}
