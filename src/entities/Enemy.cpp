#include "Enemy.hpp"

// Enemy Constructor 
Enemy::Enemy(float x, float y, int hp) : Entity(x, y, Color::Red, hp) {}

void Enemy::update(float deltaTime, Grid& grid, vector<Entity*>& players) {
    Player* detectedPlayer = nullptr;

    // Check if any player is detected
    for (auto& entity : players) {
        Player* player = dynamic_cast<Player*>(entity);
        if (player) {
            Vector2f rayOrigin(getSprite().getPosition().x, getSprite().getPosition().y);
            Vector2f rayDirection(1.f, 0.f);

            // Perform raycast to detect player
            if (raycast(rayOrigin, rayDirection, player)) {
                detectedPlayer = player;
                state.SetSeenPlayer(true);
                break;
            }
        }
    }

    // Set low health state if health is 20 or less
    if (getHealth() <= 20) {
        state.SetLow(true);
    }
    else {
        state.SetLow(false);
    }

    // Execute actions based on player detection and health status
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

// Draw the enemy and ray in the window
void Enemy::draw(RenderWindow& window) {
    window.draw(getSprite());
    window.draw(ray);
}

// Perform raycast to detect if the player is in sight
bool Enemy::raycast(const Vector2f& rayOrigin, const Vector2f& rayDirection, Player* player) {
    const float RAY_LENGTH = 500.f;

    Vector2f rayEnd = rayOrigin + rayDirection * RAY_LENGTH;
    Vector2f playerPos = player->getSprite().getPosition();
    float distanceToPlayer = sqrt(pow(playerPos.x - rayOrigin.x, 2) + pow(playerPos.y - rayOrigin.y, 2));

    // Draw the ray for debugging purposes
    ray.clear();
    ray.append(Vertex(rayOrigin, Color::Yellow));
    ray.append(Vertex(rayEnd, Color::Yellow));

    return distanceToPlayer < RAY_LENGTH;
}

// Execute the specified GOAP action
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

// Chase the player using pathfinding
void Enemy::chase(Player& player, float deltaTime, Grid& grid) {
    static Clock transitionClock, pathfindingClock;
    static float transitionDelay = 0.1f;
    static float pathfindingDelay = 0.5f;

    // Recalculate path every few seconds
    if (pathfindingClock.getElapsedTime().asSeconds() >= pathfindingDelay) {
        Vector2i enemyCell(static_cast<int>(getSprite().getPosition().x / Config::CELL_SIZE),
            static_cast<int>(getSprite().getPosition().y / Config::CELL_SIZE));
        Vector2i playerCell(static_cast<int>(player.getSprite().getPosition().x / Config::CELL_SIZE),
            static_cast<int>(player.getSprite().getPosition().y / Config::CELL_SIZE));

        // Find the path from enemy to player
        path = Pathfinding::findPath(grid, enemyCell, playerCell);
        pathfindingClock.restart();
    }

    // Move along the path with a delay between each step
    if (transitionClock.getElapsedTime().asSeconds() >= transitionDelay && !path.empty()) {
        Vector2i nextCell = path[0];
        centerOnCell(nextCell.x, nextCell.y);
        path.erase(path.begin());
        transitionClock.restart();
    }
}

// Patrol behavior (currently not implemented)
void Enemy::patrol() {}

// Flee from the player using pathfinding
void Enemy::flee(Player& player, float deltaTime, Grid& grid) {
    static Clock pathfindingClock;
    static float pathfindingDelay = 0.1f;

    Vector2f direction = getSprite().getPosition() - player.getSprite().getPosition();
    float distance = sqrt(direction.x * direction.x + direction.y * direction.y);

    // If the enemy is within the detection radius of the player, flee
    if (distance < DETECTION_RADIUS) {
        if (distance > 0) {
            direction /= distance;
            Vector2i enemyCell(static_cast<int>(getSprite().getPosition().x / Config::CELL_SIZE),
                static_cast<int>(getSprite().getPosition().y / Config::CELL_SIZE));
            Vector2i playerCell(static_cast<int>(player.getSprite().getPosition().x / Config::CELL_SIZE),
                static_cast<int>(player.getSprite().getPosition().y / Config::CELL_SIZE));

            // Calculate the path away from the player
            if (pathfindingClock.getElapsedTime().asSeconds() >= pathfindingDelay) {
                path = Pathfinding::findOppositePath(grid, enemyCell, playerCell);
                pathfindingClock.restart();
            }
        }
    }

    // Move along the path to flee
    if (!path.empty()) {
        Vector2i nextCell = path[0];
        centerOnCell(nextCell.x, nextCell.y);
        path.erase(path.begin());
    }
}
