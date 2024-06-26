#include "menu.h"

Menu::Menu(int screenWidth, int screenHeight)
{
      running = true;
      fontSize = 100;
      startScreen = true;
      selected = 0;
      isButtonPressed = false;
      buttonPressed = 0;

      lenghtOfOneLetter = MeasureText(oneLetter, fontSize);
      // menuTexts = setMenuTexts;
      menuTexts = {simuText, settingsText, quitText};

      amount = menuTexts.size();
      val = screenHeight / (amount + 1);

      for (int i = 0; i < amount; i++)
      {
            startX.push_back((screenWidth / 2) - (MeasureText(menuTexts.at(i), fontSize) / 2));
            startY.push_back(val * (i + 1) + 50);
            endX.push_back((screenWidth / 2) + (MeasureText(menuTexts.at(i), fontSize) / 2));
            endY.push_back(val * (i + 1) - 50);
      }

      backgroundImage = LoadTexture("sprites/UI-elements/SeafishTITLE.png");
}

Menu::~Menu()
{
      // UnloadTexture(backgroundImage);
}

void Menu::Draw(int screenWidth, int screenHeight)
{
      BeginDrawing();
      // Texture2D test = LoadTexture("test.png");
      ClearBackground(WHITE);
      // DrawTextureEx(backgroundImage, {0,0}, 0, 1, WHITE);

      for (int i = 0; i < menuTexts.size(); i++)
      {
            if (selected == i)
            {
                  DrawText(menuTexts.at(i), (screenWidth / 2) - (MeasureText(menuTexts.at(i), fontSize) / 2), val * (i + 1) - 50, fontSize, RED);
                  DrawLine(startX.at(i) - (lenghtOfOneLetter / 2), startY.at(i) + (lenghtOfOneLetter / 10), endX.at(i) + lenghtOfOneLetter, startY.at(i) + (lenghtOfOneLetter / 10), RED);
            }
            else
            {
                  DrawText(menuTexts.at(i), (screenWidth / 2) - (MeasureText(menuTexts.at(i), fontSize) / 2), val * (i + 1) - 50, fontSize, BLACK);
            }
      }
      EndDrawing();
}

void Menu::Update(int screenWidth, int screenHeight)
{
      if (IsKeyPressed(KEY_UP))
      {
            selected--;
            if (selected < 0)
            {
                  selected = 0;
            }
      }
      else if (IsKeyPressed(KEY_DOWN))
      {
            selected++;
            if (selected > menuTexts.size())
            {
                  selected = amount - 1;
            }
      }

      if (IsKeyPressed(KEY_W))
      {
            selected--;
            if (selected < 0)
            {
                  selected = 0;
            }
      }
      else if (IsKeyPressed(KEY_S))
      {
            selected++;
            if (selected > menuTexts.size())
            {
                  selected = amount - 1;
            }
      }

      if (1 == 2)
      { // screenheight or screenwidth or fontSize changed
            val = screenHeight / (amount + 1);
            lenghtOfOneLetter = MeasureText(oneLetter, fontSize);

            for (int i = 0; i < amount; i++)
            {
                  startX.push_back((screenWidth / 2) - (MeasureText(menuTexts.at(i), fontSize) / 2));
                  startY.push_back(val * (i + 1) + 50);
                  endX.push_back((screenWidth / 2) + (MeasureText(menuTexts.at(i), fontSize) / 2));
                  endY.push_back(val * (i + 1) - 50);
            }
      }

      if (IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(1))
      {
            buttonPressed = selected;
            isButtonPressed = true;
      }

      if (isButtonPressed)
      {
            isButtonPressed = false;
            startScreen = false;
      }
}