#include "raylib.h"
#include "movement/player.h"
#include "map/map.h"

class Game
{
private:
    Player player;
    // Tile tile = Tile(2, 3);
    Map map;

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
        // ui draw functions that should not move here

        BeginMode2D(player.camera);
            // map draw functions where things have to move here
            map.Draw();

            // DrawCircle(GetScreenWidth()/2, GetScreenHeight()/2, 100, RED);
            // DrawCircle(10, 10, 50, RED);
        EndMode2D();
    EndDrawing();
}

void Game::run() // start the game loop
{
    bool gameRunning = true;
    while (gameRunning)
    {
        Update(GetFrameTime());
        Render();
        // If quit go to main menu
        // When esc press open menu for settings, save, load, continue and exit
    }
}