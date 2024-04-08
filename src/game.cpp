#include "game.h"

Game::Game(int screenWidth, int screenHeight, int columnCount, int rowCount)
{
    // generate map using mapSize
    Vector2 startingPosition = {0, 0}; // map generation has to give starting position, which is base position 

    tileTextures = {
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

    unitTextures = {
        {"warrior1LVL1", LoadTexture("sprites/units/melee/Battlefish.png")},
        {"warrior2LVL1", LoadTexture("sprites/units/melee/BattlefishRed.png")}
    };

    tileHighLiteWhite = LoadTexture("sprites/UI-elements/hexHighlight.png");
    tileHighLiteRed = LoadTexture("sprites/UI-elements/hexRedHighlight.png");
    

    overlay = Overlay(screenWidth, screenHeight, tileTextures);
    map = Map(rowCount, columnCount, tileTextures);
    player = Player(startingPosition, screenWidth, screenHeight, &map, &tileHighLiteWhite, unitTextures);
    wave = Wave2(&map, &player.camera, &tileHighLiteWhite, unitTextures);

    gameTime = 0;
    waveCount = 0;
    score = 0;

    isCastleMenu = false;
    
    int foodTileCost = player.getTileCost("food");
    int coralTileCost = player.getTileCost("coral");
    int trainingTileCost = player.getTileCost("training");
    overlay.setTileTypeCosts(foodTileCost, coralTileCost, trainingTileCost);

    song = LoadMusicStream("music/GuitarSong.mp3");
}

Game::~Game()
{
    std::vector<std::string> unloadTileTextures = {"locked", "sea", "food", "coral", "training", "castleV1", "castleV2", "castleV3", "castleV4", "castleV5"};

    for (int i=0; i < unloadTileTextures.size(); i++) {
        UnloadTexture(tileTextures[unloadTileTextures.at(i)]);
    }
    
    std::vector<std::string> unloadUnitTextures = {"warrior1LVL1", "warrior2LVL1"};

    for (int i=0; i < unloadUnitTextures.size(); i++) {
        UnloadTexture(unitTextures[unloadUnitTextures.at(i)]);
    }

    UnloadTexture(tileHighLiteWhite);
    UnloadTexture(tileHighLiteRed);
}

void Game::Update(double dt)
{
    bool isMouseOnOverlay = overlay.isMouseOnOverlay(); // check if mouse is on overlay so it can be used for player aswell

    if(IsMouseButtonPressed(0)) { // makes build mode and overlay selction work
        Vector2 worldMousePos = GetScreenToWorld2D(GetMousePosition(), player.camera);
        Vector2 coord = map.worldPosToGridPos(worldMousePos);
        if(overlay.isBuildMode) {
            if(isMouseOnOverlay) {
                int buildTile = overlay.mouseOnBuildTile();
                if(buildTile != -1) {
                    overlay.selectBuildTile(buildTile);
                }
                // do stuff with overlay
            } else if (!isCastleMenu) {
                std::string buildTileName = overlay.getBuildTileName();
                if(buildTileName != "" && map.isSurrounded(coord) && map.isTileAvailable(coord, buildTileName)) {
                    bool isBought = player.buyTile(buildTileName);
                    if(isBought) {
                        map.changeTileType(coord, buildTileName);
                        int foodTileCost = player.getTileCost("food");
                        int coralTileCost = player.getTileCost("coral");
                        int trainingTileCost = player.getTileCost("training");
                        overlay.setTileTypeCosts(foodTileCost, coralTileCost, trainingTileCost);
                    } else {
                        std::cout << "NOT ENOUGH MONEY" << std::endl;
                        // DrawTextEx(GetFontDefault(), "NOT ENOUGH MONEY", (Vector2){GetScreenWidth() / 2, GetScreenHeight() / 2}, 50, 10, DARKGRAY);
                        // not enough money
                    }
                }
            }
        }

        std::vector<std::string> castleTypes = {"castleV1", "castleV2", "castleV3", "castleV4", "castleV5"};

        bool isMouseOnCastle = (std::find(castleTypes.begin(), castleTypes.end(), map.getTileType(coord)) != castleTypes.end());

        if(isMouseOnCastle) {
            isCastleMenu = true;
        }

        if(isCastleMenu) {
            Vector2 mousePos = GetMousePosition();
            if(mousePos.x > 1365 && mousePos.x < 1485 && mousePos.y > 500 && mousePos.y < 630) {
                isCastleMenu = false;
            }
        }

    }

    player.Update(dt, overlay.selectedBuildTile); // update all the objects that are in player
    wave.Update(dt);

    MusicPlayer(); // play the song 
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
            map.draw(); // draw the tiles

            player.Render(); // draw player units
            wave.Render();

            if(!overlay.isMouseOnOverlay() && overlay.isBuildMode && !isCastleMenu) {
                std::string buildTileName = overlay.getBuildTileName();
                if(buildTileName != "") {
                    map.drawGhostTile(coord, buildTileName, map.isSurrounded(coord));
                    // ! TODO: DRAW MONEY SHORTAGE ! //
                    // ! getTileCost is not optimized //
                    // if(player.getTileCost(buildTileName) > player.getCoralAmount()) {
                    //     Vector2 textDimentions = MeasureTextEx(GetFontDefault(), "NOT ENOUGH MONEY", 50, 10);
                    //     DrawTextEx(GetFontDefault(), "NOT ENOUGH MONEY", (Vector2){(GetScreenWidth() - textDimentions.x) / 2, (GetScreenHeight() - textDimentions.y) / 2}, 50, 10, RED);
                    // }
                    // ! END TODO ! //
                }
            }

        EndMode2D();
        
        if(isCastleMenu) {
            overlay.drawCastleMenu();
        }
        DrawText(TextFormat("coord x: %d", int(coord.x)), 100, 100, 10, BLACK);
        DrawText(TextFormat("coord y: %d", int(coord.y)), 200, 100, 10, BLACK);
        // DrawText(TextFormat("coord z: %d", int(coord.z)), 300, 100, 10, BLACK);

        // ui draw functions that should not move here
        int food = player.getFoodAmount();
        int coral = player.getCoralAmount();
        int time = int(gameTime);
        overlay.drawInventory(food, coral, score, time, waveCount, 1);

        overlay.drawBuildMode();
    EndDrawing();
}

void Game::run() // start the game loop
{
    bool gameRunning = true;
    double dt;

    player.Start();
    wave.Start();
    
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