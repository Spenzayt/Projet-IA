#include "Entity.hpp"

Entity::Entity(float x, float y, sf::Color color, int hp) : health(hp) {
    sprite.setSize({ 30, 30 });
    sprite.setPosition(x, y);
    sprite.setFillColor(color);
}

bool Entity::isAlive() const {
    return health > 0;
}

void Entity::takeDamage(int damage) {
    health = max(0, health - damage);
}

void Entity::centerOnCell(int gridX, int gridY) {
    float newX = gridX * 40 + 5;
    float newY = gridY * 40 + 5;

    sprite.setPosition(newX, newY);
}
