#include "raylib.h"

#include "player/player.h"
#include "player/overlay.h"
#include "map/map.h"

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
    void run();

    Game(int screenWidth, int screenHeight, int columnCount, int rowCount);
    ~Game();
};

Game::Game(int screenWidth, int screenHeight, int columnCount, int rowCount)
{
    // generate map using mapSize
    Vector2 startingPosition = {0, 0}; // map generation has to give starting position, which is base position 
    player = Player(startingPosition, screenWidth, screenHeight);
    overlay = Overlay(screenWidth, screenHeight);
    map = Map(31, 31, &player.camera);


    song = LoadMusicStream("music/GuitarSong.mp3");
}

Game::~Game()
{
}

void Game::Update(double dt)
{
    player.movement(dt);
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
        ClearBackground(WHITE);
        Vector2 coord;
        Vector2 posi = GetScreenToWorld2D(GetMousePosition(), player.camera); // dit voor screen pos naar world pos
        coord = map.worldPosToGridPos(posi);
        BeginMode2D(player.camera);
            // map draw functions where things have to move here
            map.draw();

            // DrawCircle(GetScreenWidth()/2, GetScreenHeight()/2, 100, RED);
            // DrawCircle(10, 10, 50, RED);
        EndMode2D();
        
        DrawText(TextFormat("coord x: %d", int(coord.x)), 100, 100, 10, BLACK);
        DrawText(TextFormat("coord y: %d", int(coord.y)), 200, 100, 10, BLACK);
        // DrawText(TextFormat("coord z: %d", int(coord.z)), 300, 100, 10, BLACK);

        // ui draw functions that should not move here
        int food = player.getFoodAmount();
        int coral = player.getCoralAmount();
        overlay.drawInventory(food, coral);
        overlay.drawBuildMode();
    EndDrawing();

    MusicPlayer();
}

void Game::run() // start the game loop
{
    bool gameRunning = true;
    double dt;
    while (gameRunning && !WindowShouldClose())
    {
        dt = GetFrameTime();
        Update(dt);
        Render();
        // If quit go to main menu
        // When esc press open menu for settings, save, load, continue and exit
    }
}