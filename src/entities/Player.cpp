#include "Player.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include "Enemy.hpp"

Player::Player(float x, float y, int hp) : Entity(x, y, Color::Blue, hp), attackTimer(0.f) {}

void Player::update(float deltaTime, Grid& grid, vector<Entity*> enemies) {
    Vector2i currentCell(static_cast<int>(sprite.getPosition().x / CELL_SIZE),
        static_cast<int>(sprite.getPosition().y / CELL_SIZE));
    Vector2i targetCell = currentCell;

    if (moveTimer >= moveDelay) {
        if (Keyboard::isKeyPressed(Keyboard::Z)) targetCell.y -= 1;
        if (Keyboard::isKeyPressed(Keyboard::S)) targetCell.y += 1;
        if (Keyboard::isKeyPressed(Keyboard::Q)) targetCell.x -= 1;
        if (Keyboard::isKeyPressed(Keyboard::D)) targetCell.x += 1;

        Vector2f targetPosition(targetCell.x * CELL_SIZE, targetCell.y * CELL_SIZE);

        auto isWalkable = [&](int x, int y) {
            return x >= 0 && x < GRID_WIDTH && y >= 0 && y < GRID_HEIGHT && grid.getCell(x, y).walkable;
            };

        if (isWalkable(targetCell.x, targetCell.y)) {
            centerOnCell(targetCell.x, targetCell.y);
        }
        moveTimer = 0.f;
    }

    moveTimer += deltaTime;

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