#pragma once
#include <map>
#include <string>
#include "raylib.h"

#include "player/player.h"
#include "player/overlay.h"
#include "map/map.h"
#include "units/unit.h"

class Game
{
private:
    Player player;
    Overlay overlay;
    Map map;
    Music song;

    void Update(double dt);
    void Render();
    void MusicPlayer();

public:
    double gameTime;
    int waveCount;
    int score;

    void run();

    Game(int screenWidth, int screenHeight, int columnCount, int rowCount);
    ~Game();
};