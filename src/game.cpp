#include "game.h"

Game::Game(int screenWidth, int screenHeight, int columnCount, int rowCount)
{
    // generate map using mapSize
    Vector2 startingPosition = {0, 0}; // map generation has to give starting position, which is base position 

    std::map<std::string, Texture2D> tileTextures = {
        {"locked", LoadTexture("sprites/resources/BlankTile.png")},
        {"sea", LoadTexture("sprites/resources/BlankTile.png")},
        {"food", LoadTexture("sprites/resources/AlgenTile.png")},
        {"coral", LoadTexture("sprites/resources/CoralTile.png")},
        {"training", LoadTexture("sprites/buildings/TrainingTile.png")},
        {"castleV1", LoadTexture("sprites/castle/CastleTileLVL1.png")},
        {"castleV2", LoadTexture("sprites/castle/CastleTileLVL2.png")},
        {"castleV3", LoadTexture("sprites/castle/CastleTileLVL3.png")},
        {"castleV4", LoadTexture("sprites/castle/CastleTileLVL4.png")},
        {"castleV5", LoadTexture("sprites/castle/CastleTileLVL5.png")}
    };

    std::map<std::string, Texture2D> unitTextures = {
        {"warriorLVL1", LoadTexture("sprites/units/melee/Battlefish.png")},
        {"warriorLVL2", LoadTexture("sprites/units/melee/BattlefishRed.png")}
    };

    overlay = Overlay(screenWidth, screenHeight, tileTextures);
    map = Map(rowCount, columnCount, tileTextures);
    player = Player(startingPosition, screenWidth, screenHeight, &map);

    gameTime = 0;
    waveCount = 0;
    score = 0;

    song = LoadMusicStream("music/GuitarSong.mp3");
}

Game::~Game()
{
}

void Game::Update(double dt)
{
    bool isMouseOnOverlay = overlay.isMouseOnOverlay();;
    if(IsMouseButtonPressed(0)) {
        if(overlay.isBuildMode) {
            if(isMouseOnOverlay) {
                int buildTile = overlay.mouseOnBuildTile();
                if(buildTile != -1) {
                    overlay.selectBuildTile(buildTile);
                }
                // do stuff with overlay
            } else {
                Vector2 worldMousePos = GetScreenToWorld2D(GetMousePosition(), player.camera);
                Vector2 coord = map.worldPosToGridPos(worldMousePos);
                std::string buildTileName = overlay.getBuildTileName();
                if(buildTileName != "" && map.isSurrounded(coord) && map.isTileAvailable(coord, buildTileName)) {
                    bool isBought = player.buyTile(buildTileName);
                    if(isBought) {
                        map.changeTileType(coord, buildTileName);
                    } else {
                        std::cout << "NOT ENOUGH MONEY" << std::endl;
                        // not enough money
                    }
                }
            }
        }

    }

    player.Update(dt, overlay.selectedBuildTile);
}

void Game::MusicPlayer() 
{
    if (!IsMusicStreamPlaying(song)) { // start song if not already playing
        PlayMusicStream(song);
    } else {
        UpdateMusicStream(song);
    }
}

void Game::Render()
{
    BeginDrawing();
        ClearBackground(BLACK);
        Vector2 worldMousePos = GetScreenToWorld2D(GetMousePosition(), player.camera); // dit voor screen pos naar world pos
        Vector2 coord = map.worldPosToGridPos(worldMousePos);
        BeginMode2D(player.camera);
            // map draw functions where things have to move here
            map.draw();

            player.Render();

            if(!overlay.isMouseOnOverlay() && overlay.isBuildMode) {
                std::string buildTileName = overlay.getBuildTileName();
                if(buildTileName != "") {
                    map.drawGhostTile(coord, buildTileName, map.isSurrounded(coord));
                }
            }
        EndMode2D();
        
        DrawText(TextFormat("coord x: %d", int(coord.x)), 100, 100, 10, BLACK);
        DrawText(TextFormat("coord y: %d", int(coord.y)), 200, 100, 10, BLACK);
        // DrawText(TextFormat("coord z: %d", int(coord.z)), 300, 100, 10, BLACK);

        // ui draw functions that should not move here
        int food = player.getFoodAmount();
        int coral = player.getCoralAmount();
        overlay.drawInventory(food, coral, score, gameTime, waveCount, 1);
        overlay.drawBuildMode();
    EndDrawing();

    // MusicPlayer();
}

void Game::run() // start the game loop
{
    bool gameRunning = true;
    double dt;

    player.Start();
    
    while (gameRunning && !WindowShouldClose())
    {
        dt = GetFrameTime();
        Update(dt);
        Render();

        gameTime += dt;
        // If quit go to main menu
        // When esc press open menu for settings, save, load, continue and exit
    }
}