#include "raylib.h"

#include "player/player.h"
#include "map/map.h"

class Game
{
private:
    Player player;
    // Tile tile = Tile(2, 3);
    Map map;
    Music song;

    void Update(double dt);
    void Render();

public:
    void run();

    Game(int screenWidth, int screenHeight, int columnCount, int rowCount);
    ~Game();
};

Game::Game(int screenWidth, int screenHeight, int columnCount, int rowCount)
{
    // generate map using mapSize
    map = Map(16, 16);

    Vector2 startingPosition = {0, 0}; // map generation has to give starting position, which is base position 
    player = Player(startingPosition, screenWidth, screenHeight);

    // song = LoadMusicStream("/music/song1");
}

Game::~Game()
{
}

void Game::Update(double dt)
{
    player.movement(dt);
}

void Game::Render()
{
    BeginDrawing();
        ClearBackground(WHITE);
        Vector2 coord;
        coord = map.worldPosToGridPos(GetMousePosition());
        BeginMode2D(player.camera);
            // map draw functions where things have to move here
            map.Draw();

            // DrawCircle(GetScreenWidth()/2, GetScreenHeight()/2, 100, RED);
            // DrawCircle(10, 10, 50, RED);
        EndMode2D();
        DrawText(TextFormat("coord x: %d", int(coord.x)), 100, 200, 10, BLACK);
        DrawText(TextFormat("coord y: %d", int(coord.y)), 200, 100, 10, BLACK);

        // ui draw functions that should not move here
        player.DrawInventory();
    EndDrawing();

    // if (!IsMusicStreamPlaying(song)) { // start song if not already playing
    //     PlayMusicStream(song);
    // }
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