#ifndef GRID_HPP
#define GRID_HPP

#include <vector>
#include <SFML/Graphics.hpp>
#include <string>
#include "../game/Config.hpp"

using namespace std;
using namespace sf;

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