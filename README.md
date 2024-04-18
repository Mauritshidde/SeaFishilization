# Sea Fishilization
Sea Fishilazition is a game we made for the Fish Fest GameJam.  
We (Maurits, Midas and Twan) made this game using C++ and Raylib.

Defend your city against waves of enemy's

Every X seconds a wave of enemy's spawn which wants to destroy your castle. It's your task to defend the castle, you have to do so by training units and placing tiles to improve your production. The more waves you have survived the bigger and stronger the waves get.

Your castle receives damage when an enemy is in a tile that surrounds the castle, the more enemy's that are surrounding the castle the more damage you receive.

You lose when your castles hp is 0, the goal of the game is surviving as long as possible.

This game is made with c++ and Raylib

## Controls / Mechanics

### Main menu
- W and S or arrow keys to select an option
- Enter Key or Right Mouse Button to start the option

### Movement
- WASD
- Mouse drag
- Mouse scroll - for zoom

- To  move units click on the tile the unit is on and select 1 of the tiles highlighted tiles. If a unit is moving or fighting you can't select the unit and have to wait until the action has been completed.

- You can upgrade the castle by clicking on it.

- You can train units by clicking on  the training camp tile, this will open an menu in which you can select the option you want by pressing the correct key. if a united was trained on a training tile there is an cool down before you can train a new unit.

- Placing tiles can be done by selecting an tile in the menu on the bottom of the screen and then placing it. NOTE: You can only place a tile if the tile is highlighted with a white color, this is only the case when the tile is adjacent to the castle tile or one of the build tiles, and you need to have enough coral to place a tile.


## Quit game
- press escape key to exit whilst in game
- select quit in main menu

## Install instructions:
you can download the game from itch.io using this link: https://mauritshidde.itch.io/sea-fishilization

(the executable(exe) has to stay in the given folder to work correctly)

### On windows:
- download the zip file
- unzip the file
- run the game.exe file in the folder

### On linux; using wine:
- download the zip file
- unzip the file
- run the game.exe file from the terminal by typing ./game.exe

### On linux without wine:
- download the zip file
- unzip the file
- run the game by typing ./game.out whilst in the game folder
NOTE: you will probably have to install raylib when using it this way: https://www.raylib.com/


### Installing github project
If you want to compile the code you need to have raylib (the makefile only compiles non staticly for linux).
There is also a makefile which compiles for windows staticly, which can also be used for linux but it will be slower, becasue it will run with wine.

run in the terminal:
```bash
git clone https://github.com/Mauritshidde/SeaFishilization.git
cd SeaFishilization
make && ./a.out
```
