class Tile {
    private: 
        /* data */
    public:
        Vector2 pos;
        int tileSize;
        int type;
        Tile(int x, int y, int size);
        int Draw();
        ~Tile();
};

Tile::Tile(int x, int y, int size = 30) {
    pos.x = x;
    pos.y = y;
    tileSize = size;
}

int Tile::Draw() {
    Color tileColor = {50, 0, 100, 255}; // temp
    DrawRectangle(pos.x * tileSize, pos.y * tileSize, tileSize, tileSize, tileColor);
    return 0;
}

Tile::~Tile() {

}