#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "Config.hpp"
#include "../entities/Player.hpp"
#include "../entities/Enemy.hpp"
#include "../map/Grid.hpp"
#include <vector>
#include <memory>

class Game {
public:
    Game();
    ~Game();
    void run();

private:
    void processEvents();
    void update(float deltaTime);
    void render();

    RenderWindow window;
    Clock clock;

    Grid grid;
    Player player;
    vector<unique_ptr<Enemy>> enemies;
};

#endif // GAME_HPP