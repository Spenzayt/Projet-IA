#include "grid.hpp"
#include <fstream>
#include <iostream>

Grid::Grid() {
    cells.resize(Config::GRID_HEIGHT, std::vector<Cell>(Config::GRID_WIDTH, { true, {0, 0}, sf::RectangleShape(sf::Vector2f(Config::CELL_SIZE, Config::CELL_SIZE)) }));
    for (int y = 0; y < Config::GRID_HEIGHT; ++y) {
        for (int x = 0; x < Config::GRID_WIDTH; ++x) {
            cells[y][x].position = sf::Vector2f(x * Config::CELL_SIZE, y * Config::CELL_SIZE);
            cells[y][x].sprite.setPosition(cells[y][x].position);
            cells[y][x].sprite.setFillColor(sf::Color::Transparent);
            cells[y][x].sprite.setOutlineThickness(1);
            cells[y][x].sprite.setOutlineColor(sf::Color(50, 50, 50));
        }
    }
}

void Grid::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier " << filename << std::endl;
        return;
    }

    for (int y = 0; y < Config::GRID_HEIGHT; ++y) {
        std::string line;
        if (!std::getline(file, line)) break;
        for (int x = 0; x < Config::GRID_WIDTH && x < line.size(); ++x) {
            cells[y][x].walkable = (line[x] == '0');
            if (!cells[y][x].walkable) {
                cells[y][x].sprite.setFillColor(sf::Color::White);
            }
        }
    }
}

void Grid::draw(sf::RenderWindow& window) {
    for (int y = 0; y < Config::GRID_HEIGHT; ++y) {
        for (int x = 0; x < Config::GRID_WIDTH; ++x) {
            window.draw(cells[y][x].sprite);
        }
    }
}

Cell& Grid::getCell(int x, int y) {
    return cells[y][x];
}