#include <vector>
#include <string>
#include "../raylib.h"

#include "../map/tile.h"
#include "../map/map.h"
#include "unit.h"

class UnitInventory
{
private:
    bool isAlive(Unit *unit);
    void removeDead();

    Map *map;
    Camera2D *camera;

    Texture2D tileHighLite;
    Texture2D warrior1;
    Texture2D warrior2;
public:
    std::string owner;
    std::vector<Unit> units;

    void createUnit(int maxHealth, double damage, double movementSpeed, Vector2 startingPos, Camera2D *test);
    void Update(double dt);
    void Render();

    UnitInventory(std::string setOnwer = "player", Map *setMap = NULL, Camera2D *setCamera = NULL);
    ~UnitInventory();
};