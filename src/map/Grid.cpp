#include "Grid.hpp"

// sGrid Constructor
Grid::Grid() {
    // Initialize the grid with walkable cells
    cells.resize(Config::GRID_HEIGHT, std::vector<Cell>(Config::GRID_WIDTH, { true, {0, 0}, RectangleShape(Vector2f(Config::CELL_SIZE, Config::CELL_SIZE)) }));

    // Position each cell and set up its appearance
    for (int y = 0; y < Config::GRID_HEIGHT; ++y) {
        for (int x = 0; x < Config::GRID_WIDTH; ++x) {
            cells[y][x].position = Vector2f(x * Config::CELL_SIZE, y * Config::CELL_SIZE);
            cells[y][x].sprite.setPosition(cells[y][x].position);
            cells[y][x].sprite.setFillColor(Color::Transparent);
            cells[y][x].sprite.setOutlineThickness(1);
            cells[y][x].sprite.setOutlineColor(Color(50, 50, 50));
        }
    }
}

void Grid::loadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file) {
        std::cerr << "Error: Cannot open file " << filename << std::endl;
        return;
    }

    // Read each line from the file and set cells as walkable or not
    for (int y = 0; y < Config::GRID_HEIGHT; ++y) {
        string line;
        if (!getline(file, line)) break;
        for (int x = 0; x < Config::GRID_WIDTH && x < line.size(); ++x) {
            cells[y][x].walkable = (line[x] == '0'); // 0 means walkable, other means non-walkable
            if (!cells[y][x].walkable) {
                cells[y][x].sprite.setFillColor(Color::White); // Non-walkable cells in white
            }
        }
    }
}

// Draw all the cells on the window
void Grid::draw(RenderWindow& window) {
    for (int y = 0; y < Config::GRID_HEIGHT; ++y) {
        for (int x = 0; x < Config::GRID_WIDTH; ++x) {
            window.draw(cells[y][x].sprite);
        }
    }
}

Cell& Grid::getCell(int x, int y) {
    return cells[y][x];
}

// Check if the cell is walkable
bool Grid::isCellWalkable(int x, int y) {
    return cells[y][x].walkable;
}

// Convert world position to cell position
Vector2i Grid::worldToCell(const Vector2f& worldPosition) const {
    int x = static_cast<int>(worldPosition.x / Config::CELL_SIZE);
    int y = static_cast<int>(worldPosition.y / Config::CELL_SIZE);
    return Vector2i(x, y);
}