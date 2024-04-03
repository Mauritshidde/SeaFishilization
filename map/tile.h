class Tile 
{
private: 
    int tileSize;
    int type;
public:
    Vector2 pos;
    Tile(int x = 0, int y = 0, int size = 30);
    int Draw();
    ~Tile();
};

Tile::Tile(int x, int y, int size) 
{
    pos.x = x;
    pos.y = y;
    tileSize = size;
}

int Tile::Draw() 
{
    Color tileColor = {110, 125, 150, 255}; // temp
    DrawRectangle(pos.x * tileSize, pos.y * tileSize, tileSize -1, tileSize -1, tileColor);
    return 0;
}

Tile::~Tile() {

}