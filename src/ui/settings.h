#pragma once
#include <vector>
#include <raylib.h>

class Settings
{
private:
    const char *oneLetter = "A";
    const char *simuText = "Start Game";
    const char *settingsText = "Settings";
    const char *quitText = "Quit";

    float fontSize;
    int amount;
    float val;

    bool isButtonPressed;
    int selected;

    float lenghtOfOneLetter;

    std::vector<const char *> settingsTexts;
    std::vector<float> startX, startY, endX, endY;

public:
    int buttonPressed;
    bool running;
    bool startScreen;
    void Draw(int screenWidth, int screenHeight);
    void Update(int screenWidth, int screenHeight);

    Settings(int screenWidth = 1920, int screenHeight = 1080);
    ~Settings();
};
