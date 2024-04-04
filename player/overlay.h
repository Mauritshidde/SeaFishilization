#include "../raylib.h"

class Overlay
{
private:
    int screenWidth;
    int screenHeight;
public:
    void drawBuildMode();
    void drawInventory(int food, int coral);
    Overlay(int screenWidth, int screenHeight);
    ~Overlay();
};

Overlay::Overlay(int screenWidth_ = 1920, int screenHeight_ = 1084) {
    screenWidth = screenWidth_;
    screenHeight = screenHeight_;
}

Overlay::~Overlay() {
    
}

void Overlay::drawBuildMode() {
    
}

void Overlay::drawInventory(int food, int coral) {
    DrawRectangle(screenWidth - screenWidth/4, 0, screenWidth/4, screenHeight/10, BLACK);

    DrawText(TextFormat("Food: %d", food), screenWidth - screenWidth/8, screenHeight/20, 10, WHITE);
    DrawText(TextFormat("Coral: %d", coral), screenWidth - screenWidth/4, screenHeight/20, 10, WHITE);
}
