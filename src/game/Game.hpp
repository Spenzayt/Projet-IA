#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "../entities/Player.hpp"
#include "../entities/Enemy.hpp"
#include "../map/Grid.hpp"
#include <vector>

class Game {
public:
    Game();
    ~Game();

    void run();

private:
    sf::RenderWindow window;
    Player player;
    std::vector<Enemy> enemies;
    Grid grid;

    void processEvents();
    void update(float deltaTime);
    void render();
};

#endif // GAME_HPP