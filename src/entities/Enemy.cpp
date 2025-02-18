#include "Enemy.hpp"
#include <cmath>
#include <iostream>

Enemy::Enemy(float x, float y, int hp) : Entity(x, y, sf::Color::Red, hp) {}

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
    static Clock transitionClock, pathfindingClock;
    static float transitionDelay = 0.1f;
    static float pathfindingDelay = 0.5f;

    if (pathfindingClock.getElapsedTime().asSeconds() >= pathfindingDelay) {
        Vector2i enemyCell(static_cast<int>(sprite.getPosition().x / CELL_SIZE),
            static_cast<int>(sprite.getPosition().y / CELL_SIZE));
        Vector2i playerCell(static_cast<int>(player.sprite.getPosition().x / CELL_SIZE),
            static_cast<int>(player.sprite.getPosition().y / CELL_SIZE));

        path = Pathfinding::findPath(grid, enemyCell, playerCell);

        pathfindingClock.restart();
    }

    if (transitionClock.getElapsedTime().asSeconds() >= transitionDelay && !path.empty()) {
        Vector2i nextCell = path[0];
        centerOnCell(nextCell.x, nextCell.y);
        path.erase(path.begin());

        transitionClock.restart();
    }
}

void Enemy::patrol() {}

void Enemy::flee(Player& player, float deltaTime, Grid& grid) {
    static Clock pathfindingClock;
    static float pathfindingDelay = 0.1f;

    Vector2f direction = sprite.getPosition() - player.sprite.getPosition();
    float distance = sqrt(direction.x * direction.x + direction.y * direction.y);

    if (distance < DETECTION_RADIUS) {
        if (distance > 0) {
            direction /= distance;
            Vector2i enemyCell(static_cast<int>(sprite.getPosition().x / CELL_SIZE),
                static_cast<int>(sprite.getPosition().y / CELL_SIZE));
            Vector2i playerCell(static_cast<int>(player.sprite.getPosition().x / CELL_SIZE),
                static_cast<int>(player.sprite.getPosition().y / CELL_SIZE));

            if (pathfindingClock.getElapsedTime().asSeconds() >= pathfindingDelay) {
                path = Pathfinding::findOppositePath(grid, enemyCell, playerCell);

                pathfindingClock.restart();
            }
        }
    }

    if (!path.empty()) {
        Vector2i nextCell = path[0];
        centerOnCell(nextCell.x, nextCell.y);
        path.erase(path.begin());
    }
}
