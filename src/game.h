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
#include "gameOver.h"

class Game
{
private:
    Player player;
    Overlay overlay;
    Map map;
    Music song;
    Wave2 wave;
    GameOver gameOverScreen;

    std::vector<std::string> castleTypes;
    bool isCastleMenu;
    bool isTrainingMenu;
    bool gameRunning;
    
    Tile *selectedTrainingTile;

    std::map<std::string, Texture2D> tileTextures;
    std::map<std::string, Texture2D> unitTextures;
    Texture2D tileHighLiteWhite;
    Texture2D tileHighLiteRed;

    Vector2 trainingTileLocation;

    double noMoneyMsgCountDown = 0;

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