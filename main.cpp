#include <vector>
#include <iostream>
#include "raylib.h"

#include "ui/menu.h"
#include "ui/settings.h"

#include "game.h"

int screenWidth = 0;
int screenHeight = 0;

int main()
{
    bool quitGame = false;

    InitWindow(0, 0, "SeaFishilisation I");
    SetTargetFPS(60);
    Menu menu;
    Settings settingsMenu;

    screenWidth = GetScreenWidth();
    screenHeight = GetScreenHeight();
    menu = Menu(screenWidth, screenHeight);
    settingsMenu = Settings(screenWidth, screenHeight);

    // for the main menu maybe add 

    while (!quitGame && !WindowShouldClose()) // dit is de gameloop voor het mainMenu deze zolang deze acttief is runt de game
    {       
        while (menu.startScreen) // deze loop gaat door tot je een keuze hebt gemaakt in het main menu
        {
            menu.Update(screenWidth, screenHeight);
            menu.Draw(screenWidth, screenHeight);
        }
        menu.startScreen = true; // set menu screen back to true so that when you quit to main menu you gt back to the main menu screen

        if (menu.buttonPressed == 0) // optie 1 start game
        {
            Game game(screenWidth, screenHeight, 10, 10);
            game.run();
            // dit moet worden vervangen met een functie of class die in een andere file moet
            // while (!WindowShouldClose())
            // {
            //     Start();
            //     Update();
            //     Render();
            // }

            // set game closed to flase again so a game can be restarted
        }
        else if (menu.buttonPressed == 1) // optie 2 settings
        {
            while (settingsMenu.startScreen)
            {
                settingsMenu.Update(screenWidth, screenHeight);
                settingsMenu.Draw(screenWidth, screenHeight);
            }
                std::cout<< "end ? test" <<std::endl;

            settingsMenu.startScreen = true; // same reason as for main menu, and declaration not in this if becuase this is better for response time, but worse for start up time
        }
        else // optie 3 quit game
        {
            quitGame = true;
        }
    }

    return 0;
}