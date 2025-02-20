#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>
#include "../game/Config.hpp"
#include "../map/Grid.hpp"

using namespace std;
using namespace sf;

class Entity {
public:
    RectangleShape sprite;
    Vector2f velocity;
    int health;

    Entity(float x, float y, Color color, int hp);
    virtual void update(float deltaTime, Grid& grid, vector<Entity*>& entities) = 0;
    virtual void draw(RenderWindow& window) = 0;

    bool isAlive() const;
    void takeDamage(int damage);
    void centerOnCell(int gridX, int gridY);

    RectangleShape& getSprite() { return sprite; }
    int getHealth() const { return health; }
};

#endif // ENTITY_HPP