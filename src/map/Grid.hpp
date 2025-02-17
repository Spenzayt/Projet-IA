#ifndef GRID_HPP
#define GRID_HPP

#include <vector>
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;
using namespace sf;

const int GRID_WIDTH = 48;
const int GRID_HEIGHT = 27;
const int CELL_SIZE = 40;

struct Cell {
    bool walkable;
    Vector2f position;
    RectangleShape sprite;
};

class Grid {
public:
    Grid();
    void loadFromFile(const string& filename);
    void draw(RenderWindow& window);
    Cell& getCell(int x, int y);
private:
    vector<vector<Cell>> cells;
};

#endif