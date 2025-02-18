#include "Enemy.hpp"
#include <cmath>
#include <iostream>

Enemy::Enemy(float x, float y, int hp, Player* _p) : p(_p), Entity(x, y, sf::Color::Red, hp) {


    currentState = PATROL;
}

void Enemy::update(float deltaTime, Grid& grid, std::vector<Entity*> players) {
    Player* detectedPlayer = nullptr;

    for (auto& entity : players) {
        Player* player = dynamic_cast<Player*>(entity);
        if (player) {
            float distance = sqrt(pow(player->sprite.getPosition().x - sprite.getPosition().x, 2) +
                pow(player->sprite.getPosition().y - sprite.getPosition().y, 2));

            if (distance <= DETECTION_RADIUS) {
                detectedPlayer = player;
                state.SetSeenPlayer(true);
                break;
            }
        }
    }

    if (health <= 20) {
        state.SetLow(true);
    }
    else {
        state.SetLow(false);
    }

    if (state.IsLow() && detectedPlayer) {
        executeGoapAction("Flee", deltaTime, grid, detectedPlayer);
    }
    else if (state.HasSeenPlayer() && detectedPlayer) {
        executeGoapAction("Chase", deltaTime, grid, detectedPlayer);
    }
    else {
        executeGoapAction("Patrol", deltaTime, grid, nullptr);
    }
}

void Enemy::FSM(Player& _p, vector<Entity*> players, float deltaTime, Grid& grid) {

    Vector2f playerPos = p->getPosition();

    switch (currentState) {
    case PATROL:
        patrol();
       /* if (detectedPlayer(vector<Entity*> entity.getPosition())) currentState = CHASE;*/
        break;
    case CHASE:
        chase(_p, deltaTime, grid);
        /*if (!detectedPlayer(players->sprite.getPosition()) {
            lastPlayerPosition = player
                currentState = SEARCH;
        }*/
        break;
    case SEARCH:
        /*search(lastPlayerPosition, deltaTime);*/
            break;
    }

}

void Enemy::executeGoapAction(const std::string& actionName, float deltaTime, Grid& grid, Player* player) {
    if (actionName == "Chase" && player) {
        chase(*player, deltaTime, grid);
    }
    else if (actionName == "Flee" && player) {
        flee(*player, deltaTime, grid);
    }
    else if (actionName == "Patrol") {
        patrol();
    }
}

void Enemy::chase(Player& player, float deltaTime, Grid& grid) {
    Vector2f direction = player.sprite.getPosition() - sprite.getPosition();
    float distance = sqrt(direction.x * direction.x + direction.y * direction.y);

    if (distance > 0) {
        direction /= distance;
        Vector2f newPosition = sprite.getPosition() + direction * SPEED * deltaTime;

        auto isWalkable = [&](float x, float y) {
            int gridX = static_cast<int>(x / CELL_SIZE);
            int gridY = static_cast<int>(y / CELL_SIZE);
            return gridX >= 0 && gridX < GRID_WIDTH && gridY >= 0 && gridY < GRID_HEIGHT && grid.getCell(gridX, gridY).walkable;
            };

        bool canMove = true;

        if (!isWalkable(newPosition.x - 2, newPosition.y - 2) ||
            !isWalkable(newPosition.x + 2, newPosition.y - 2) ||
            !isWalkable(newPosition.x - 2, newPosition.y + 2) ||
            !isWalkable(newPosition.x + 2, newPosition.y + 2)) {
            canMove = false;
        }
        if (!isWalkable(newPosition.x, newPosition.y) ||
            !isWalkable(newPosition.x + sprite.getSize().x, newPosition.y) ||
            !isWalkable(newPosition.x, newPosition.y + sprite.getSize().y) ||
            !isWalkable(newPosition.x + sprite.getSize().x, newPosition.y + sprite.getSize().y)) {
            canMove = false;
        }
        if (canMove) {
            sprite.move(direction * SPEED * deltaTime);
        }
    }
}

void Enemy::patrol() {}

void Enemy::flee(Player& player, float deltaTime, Grid& grid) {
    Vector2f direction = sprite.getPosition() - player.sprite.getPosition();
    float distance = sqrt(direction.x * direction.x + direction.y * direction.y);

    if (distance < 200) {
        if (distance > 0) {
            direction /= distance;
            Vector2f newPosition = sprite.getPosition() + direction * SPEED * deltaTime;

            auto isWalkable = [&](float x, float y) {
                int gridX = static_cast<int>(x / CELL_SIZE);
                int gridY = static_cast<int>(y / CELL_SIZE);
                return gridX >= 0 && gridX < GRID_WIDTH && gridY >= 0 && gridY < GRID_HEIGHT && grid.getCell(gridX, gridY).walkable;
                };

            bool canMove = true;

            if (!isWalkable(newPosition.x - 2, newPosition.y - 2) ||
                !isWalkable(newPosition.x + 2, newPosition.y - 2) ||
                !isWalkable(newPosition.x - 2, newPosition.y + 2) ||
                !isWalkable(newPosition.x + 2, newPosition.y + 2)) {
                canMove = false;
            }
            if (!isWalkable(newPosition.x, newPosition.y) ||
                !isWalkable(newPosition.x + sprite.getSize().x, newPosition.y) ||
                !isWalkable(newPosition.x, newPosition.y + sprite.getSize().y) ||
                !isWalkable(newPosition.x + sprite.getSize().x, newPosition.y + sprite.getSize().y)) {
                canMove = false;
            }
            if (canMove) {
                sprite.move(direction * SPEED * deltaTime);
            }
        }
    }
}