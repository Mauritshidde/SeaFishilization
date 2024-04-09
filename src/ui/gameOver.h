#pragma once
#include <vector>
#include "../raylib.h"

class GameOver
{
private:
    const char *oneLetter = "A";
    const char *game = "Game Over";
    const char *simuText = "Score";
    const char *settingsText = "Back to Main Menu";

    float fontSize;
    int amount;
    float val;

    bool isButtonPressed;
    int selected;

    float lenghtOfOneLetter;

    std::vector<const char *> gameOverTexts;
    std::vector<float> startX, startY, endX, endY;

    Texture2D backgroundImage;
public:
    int buttonPressed;
    bool running;
    bool startScreen;
    void Draw(int screenWidth, int screenHeight, double time);
    void Update(int screenWidth, int screenHeight);

    GameOver(int screenWidth = 1920, int screenHeight = 1080);
    ~GameOver();
};