#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "../entities/Player.hpp"
#include "../entities/Enemy.hpp"
#include "../map/Grid.hpp"
#include <vector>

using namespace std;
using namespace sf;

class Game {
public:
    Game();
    ~Game();

    void run();

private:
    RenderWindow window;
    Player player;
    vector<Enemy> enemies;
    Grid grid;

    void processEvents();
    void update(float deltaTime);
    void render();
};

#endif // GAME_HPP