#include "Player.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include "Enemy.hpp"

Player::Player(float x, float y, int hp) : Entity(x, y, Color::Blue, hp), attackTimer(0.f) {}

void Player::update(float deltaTime, Grid& grid, vector<Entity*> enemies) {
    Vector2f movement(0.f, 0.f);
    if (Keyboard::isKeyPressed(Keyboard::Z)) movement.y -= SPEED * deltaTime;
    if (Keyboard::isKeyPressed(Keyboard::S)) movement.y += SPEED * deltaTime;
    if (Keyboard::isKeyPressed(Keyboard::Q)) movement.x -= SPEED * deltaTime;
    if (Keyboard::isKeyPressed(Keyboard::D)) movement.x += SPEED * deltaTime;

    Vector2f newPosition = sprite.getPosition() + movement;
    FloatRect newBounds(newPosition, sprite.getSize());

    auto isWalkable = [&](float x, float y) {
        int gridX = static_cast<int>(x / CELL_SIZE);
        int gridY = static_cast<int>(y / CELL_SIZE);
        return gridX >= 0 && gridX < GRID_WIDTH && gridY >= 0 && gridY < GRID_HEIGHT && grid.getCell(gridX, gridY).walkable;
        };

    if (isWalkable(newBounds.left - 2, newBounds.top - 2) &&
        isWalkable(newBounds.left + newBounds.width + 2, newBounds.top - 2) &&
        isWalkable(newBounds.left - 2, newBounds.top + newBounds.height + 2) &&
        isWalkable(newBounds.left + newBounds.width + 2, newBounds.top + newBounds.height + 2)) {
        sprite.move(movement);
    }

    attackTimer += deltaTime;
    if (Mouse::isButtonPressed(Mouse::Left) && attackTimer >= ATTACK_COOLDOWN) {
        attack(enemies);
        attackTimer = 0.f;
    }
}

void Player::attack(vector<Entity*>enemies) {
    for (auto& enemy : enemies) {
        if (enemy == dynamic_cast<Enemy*>(enemy)) {
            if (enemy->isAlive() && sprite.getGlobalBounds().intersects(enemy->sprite.getGlobalBounds())) {
                enemy->takeDamage(DAMAGE);
                cout << "Enemy HP: " << enemy->health << endl;
            }
        }

    }
    cout << "Player attacks" << endl;
}

Vector2f Player::getPosition() const {
    return sprite.getPosition();
}