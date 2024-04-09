#pragma once
#include <map>
#include <vector>
#include <string>
#include "raylib.h"

#include "player/player.h"
#include "player/overlay.h"
#include "map/map.h"
#include "units/unit.h"
#include "waves/wave.h"

class Game
{
private:
    Player player;
    Overlay overlay;
    Map map;
    Music song;
    Wave2 wave;

    std::vector<std::string> castleTypes;
    bool isCastleMenu;
    bool isTrainingMenu;
    bool gameRunning;

    std::map<std::string, Texture2D> tileTextures;
    std::map<std::string, Texture2D> unitTextures;
    Texture2D tileHighLiteWhite;
    Texture2D tileHighLiteRed;

    void Update(double dt);
    void Render();
    void Start();
    void MusicPlayer();

public:
    Tile *mapCenter;
    std::vector<Tile*> surroundingCenter;
    double gameTime;
    int waveCount;
    int score;

    void run();

    Game(int screenWidth, int screenHeight, int columnCount, int rowCount);
    ~Game();
};