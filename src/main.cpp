#include <vector>
#include <iostream>
#include "raylib.h"

#include "ui/menu.h"

int screenWidth = 0;
int screenHeight = 0;

void Draw2DGrid()
{
    DrawLine(0, 0, screenWidth, 0, BLACK);
}

void Start()
{
}

void Update()
{
}

void Render()
{
    BeginDrawing();
    ClearBackground(WHITE);
    Draw2DGrid();
    EndDrawing();
}

int main()
{
    InitWindow(0, 0, "airplane simulation");
    ToggleFullscreen();
    SetTargetFPS(60);
    Menu menu;

    screenWidth = GetScreenWidth();
    screenHeight = GetScreenHeight();
    menu = Menu(screenWidth, screenHeight);

    while (menu.startScreen)
    {
        menu.Update(screenWidth, screenHeight);
        menu.Draw(screenWidth, screenHeight);
    }

    if (menu.buttonPressed == 1) {
        std::cout << "ja" << std::endl;
    }

    while (!WindowShouldClose())
    {
        Start();
        Update();
        Render();
    }

    return 0;
}