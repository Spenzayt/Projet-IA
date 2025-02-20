#include "Player.hpp"

// Player Constructor 
Player::Player(float x, float y, int hp) : Entity(x, y, Color::Blue, hp), attackTimer(0.f) {}

void Player::update(float deltaTime, Grid& grid, vector<Entity*>& enemies) {
    Vector2i currentCell(static_cast<int>(getSprite().getPosition().x / Config::CELL_SIZE),
        static_cast<int>(getSprite().getPosition().y / Config::CELL_SIZE));
    Vector2i targetCell = currentCell;

    // Handle player movement based on keyboard input
    if (moveTimer >= moveDelay) {
        if (Keyboard::isKeyPressed(Keyboard::Z)) targetCell.y -= 1;
        if (Keyboard::isKeyPressed(Keyboard::S)) targetCell.y += 1;
        if (Keyboard::isKeyPressed(Keyboard::Q)) targetCell.x -= 1;
        if (Keyboard::isKeyPressed(Keyboard::D)) targetCell.x += 1;

        // Check if the target cell is walkable
        if (grid.isCellWalkable(targetCell.x, targetCell.y)) {
            centerOnCell(targetCell.x, targetCell.y);
            moveTimer = 0.f;
        }
    }
    else {
        moveTimer += deltaTime;
    }

    // Handle attack timing and actions
    attackTimer += deltaTime;
    if (attackTimer >= ATTACK_COOLDOWN) {
        attack(enemies);
        attackTimer = 0.f;
    }
}

// Draw the player sprite on the window
void Player::draw(RenderWindow& window) {
    window.draw(getSprite());
}

// Perform an attack on nearby enemies
void Player::attack(vector<Entity*>& enemies) {
    for (auto& entity : enemies) {
        Enemy* enemy = dynamic_cast<Enemy*>(entity);
        if (enemy && getSprite().getGlobalBounds().intersects(enemy->getSprite().getGlobalBounds())) {
            enemy->takeDamage(DAMAGE);
        }
    }
}