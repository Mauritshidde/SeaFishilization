#include "gameOver.h"

GameOver::GameOver(int screenWidth, int screenHeight)
{
      running = true;
      fontSize = 100;
      startScreen = true;
      selected = 0;
      isButtonPressed = false;
      buttonPressed = 0;

      lenghtOfOneLetter = MeasureText(oneLetter, fontSize);
      // gameOverTexts = setgameOverTexts;
      gameOverTexts = {simuText, settingsText};

      amount = gameOverTexts.size();
      val = screenHeight / (amount + 1);

      for (int i = 0; i < amount; i++)
      {
            startX.push_back((screenWidth / 2) - (MeasureText(gameOverTexts.at(i), fontSize) / 2));
            startY.push_back(val * (i + 1) + 50);
            endX.push_back((screenWidth / 2) + (MeasureText(gameOverTexts.at(i), fontSize) / 2));
            endY.push_back(val * (i + 1) - 50);
      }

      backgroundImage = LoadTexture("sprites/UI-elements/SeafishTITLE.png");
}

GameOver::~GameOver()
{
      // UnloadTexture(backgroundImage);
}

void GameOver::Draw(int screenWidth, int screenHeight, double time)
{
      BeginDrawing();
      // Texture2D test = LoadTexture("test.png");
      ClearBackground(WHITE);
      // DrawTextureEx(backgroundImage, {0,0}, 0, 1, WHITE);

      for (int i = 0; i < gameOverTexts.size(); i++)
      {
            if (i == 0) {
                  DrawText(TextFormat("You survived for: %d", int(time), "%d econds"), (screenWidth / 2) - (MeasureText(gameOverTexts.at(i), fontSize) / 2), val * (i + 1) - 50, fontSize, BLACK);
            } else {
                  if (selected == i)
                  {
                        DrawText(gameOverTexts.at(i), (screenWidth / 2) - (MeasureText(gameOverTexts.at(i), fontSize) / 2), val * (i + 1) - 50, fontSize, RED);
                        DrawLine(startX.at(i) - (lenghtOfOneLetter / 2), startY.at(i) + (lenghtOfOneLetter / 10), endX.at(i) + lenghtOfOneLetter, startY.at(i) + (lenghtOfOneLetter / 10), RED);
                  }
                  else
                  {
                        DrawText(gameOverTexts.at(i), (screenWidth / 2) - (MeasureText(gameOverTexts.at(i), fontSize) / 2), val * (i + 1) - 50, fontSize, BLACK);
                  }
            }
      }
      EndDrawing();
}

void GameOver::Update(int screenWidth, int screenHeight)
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
            if (selected > gameOverTexts.size())
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
            if (selected > gameOverTexts.size())
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
                  startX.push_back((screenWidth / 2) - (MeasureText(gameOverTexts.at(i), fontSize) / 2));
                  startY.push_back(val * (i + 1) + 50);
                  endX.push_back((screenWidth / 2) + (MeasureText(gameOverTexts.at(i), fontSize) / 2));
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