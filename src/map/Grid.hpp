#ifndef GRID_HPP
#define GRID_HPP

#include <SFML/Graphics.hpp>
#include "../game/Config.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

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
    bool isCellWalkable(int x, int y);
    Vector2i worldToCell(const Vector2f& worldPosition) const;

private:
    vector<vector<Cell>> cells;
};

#endif // GRID_HPP