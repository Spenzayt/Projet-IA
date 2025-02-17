#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>
#include "../map/Grid.hpp"

using namespace std;
using namespace sf;

class Entity {
public:
    RectangleShape sprite;
    Vector2f velocity;
    int health;

    Entity(float x, float y, Color color, int hp);
    virtual void update(float deltaTime, Grid& grid, vector<Entity*> neededEntities) = 0;
    bool isAlive() const;
    void takeDamage(int damage);
};

#endif // ENTITY_HPP