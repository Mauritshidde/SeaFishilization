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
public:
    std::string owner;
    std::vector<Unit> units;

    void createUnit(int maxHealth, double damage, double movementSpeed, std::string onwer, Vector2 startingPos);
    void Update(double dt);

    UnitInventory(std::string setOnwer = "player", Map *setMap = NULL, Camera2D *setCamera = NULL);
    ~UnitInventory();
};