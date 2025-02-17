#include "Entity.hpp"

Entity::Entity(float x, float y, sf::Color color, int hp) : health(hp) {
    sprite.setSize({ 36, 36 });
    sprite.setPosition(x, y);
    sprite.setFillColor(color);
}

bool Entity::isAlive() const {
    return health > 0;
}

void Entity::takeDamage(int damage) {
    health = max(0, health - damage);
}