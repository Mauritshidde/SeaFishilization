#include "settings.h"

Settings::Settings(int screenWidth, int screenHeight)
{
      running = true;
      fontSize = 100;
      startScreen = true;
      selected = 0;
      isButtonPressed = false;
      buttonPressed = 0;

      lenghtOfOneLetter = MeasureText(oneLetter, fontSize);
      settingsTexts = {simuText, settingsText, quitText};

      amount = settingsTexts.size();
      val = screenHeight / (amount + 1);

      for (int i = 0; i < amount; i++)
      {
            startX.push_back((screenWidth / 2) - (MeasureText(settingsTexts.at(i), fontSize) / 2));
            startY.push_back(val * (i + 1) + 50);
            endX.push_back((screenWidth / 2) + (MeasureText(settingsTexts.at(i), fontSize) / 2));
            endY.push_back(val * (i + 1) - 50);
      }
}

Settings::~Settings()
{
}

void Settings::Draw(int screenWidth, int screenHeight)
{
      BeginDrawing();
      ClearBackground(WHITE);

      for (int i = 0; i < settingsTexts.size(); i++)
      {
            if (selected == i)
            {
                  DrawText(settingsTexts.at(i), (screenWidth / 2) - (MeasureText(settingsTexts.at(i), fontSize) / 2), val * (i + 1) - 50, fontSize, RED);
                  DrawLine(startX.at(i) - (lenghtOfOneLetter / 2), startY.at(i) + (lenghtOfOneLetter / 10), endX.at(i) + lenghtOfOneLetter, startY.at(i) + (lenghtOfOneLetter / 10), RED);
            }
            else
            {
                  DrawText(settingsTexts.at(i), (screenWidth / 2) - (MeasureText(settingsTexts.at(i), fontSize) / 2), val * (i + 1) - 50, fontSize, BLACK);
            }
      }
      EndDrawing();
}

void Settings::Update(int screenWidth, int screenHeight)
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
            if (selected > settingsTexts.size())
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
                  startX.push_back((screenWidth / 2) - (MeasureText(settingsTexts.at(i), fontSize) / 2));
                  startY.push_back(val * (i + 1) + 50);
                  endX.push_back((screenWidth / 2) + (MeasureText(settingsTexts.at(i), fontSize) / 2));
                  endY.push_back(val * (i + 1) - 50);
            }
      }

      if (IsMouseButtonPressed(0))
      {
            for (int i = 0; i < amount; i++)
            {
                  if (CheckCollisionPointRec(GetMousePosition(), {startX.at(i), endX.at(i), startY.at(i), endY.at(i)}))
                  {
                        buttonPressed = i;
                        isButtonPressed = true;
                        break;
                  }
            }
      }
      else if (IsKeyPressed(KEY_ENTER))
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