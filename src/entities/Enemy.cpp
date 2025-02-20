#include "Enemy.hpp"

// Enemy Constructor 
Enemy::Enemy(float x, float y, int hp) : Entity(x, y, Color::Red, hp), currentState(PatrolState::Patrolling), currentPatrolPointIndex(0), pauseDuration(2.0f) {
    patrolPoints[0] = { 40 * 43, 40 * 4 };
    patrolPoints[1] = { 40 * 43, 40 * 22 };
    patrolPoints[2] = { 40 * 4, 40 * 22 };
    patrolPoints[3] = { 40 * 4, 40 * 4 };
}

void Enemy::update(float deltaTime, Grid& grid, vector<Entity*>& players) {
    Player* detectedPlayer = nullptr;

    // Check if any player is detected
    for (auto& entity : players) {
        Player* player = dynamic_cast<Player*>(entity);
        if (player) {
            Vector2f enemyPosition = getSprite().getPosition();
            Vector2f playerPosition = player->getSprite().getPosition();

            float distance = sqrt(pow(playerPosition.x - enemyPosition.x, 2) + pow(playerPosition.y - enemyPosition.y, 2));

            // Check if the player is within detection radius
            if (distance <= DETECTION_RADIUS) {
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

    // Handle states
    if (state.IsLow() && detectedPlayer) {
        executeGoapAction("Flee", deltaTime, grid, detectedPlayer);
    }
    else if (state.HasSeenPlayer() && detectedPlayer) {
        setState(PatrolState::Alerted);
        executeGoapAction("Chase", deltaTime, grid, detectedPlayer);
    }
    else if (currentState == PatrolState::Alerted && pauseClock.getElapsedTime().asSeconds() >= 1.0f) {
        setState(PatrolState::Patrolling);
        executeGoapAction("Patrol", deltaTime, grid, nullptr);
    }
    else {
        executeGoapAction("Patrol", deltaTime, grid, nullptr);
    }
}

// Draw the enemy sprite on the window
void Enemy::draw(RenderWindow& window) {
    window.draw(getSprite());
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
        patrol(deltaTime, grid);
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

void Enemy::patrol(float deltaTime, Grid& grid) {
    // Check if the enemy is still in the pause state
    if (pauseClock.getElapsedTime().asSeconds() < pauseDuration) {
        return;
    }

    static Clock transitionClock;
    static float transitionDelay = 0.1f;

    // Get the current position of the enemy in the grid
    Vector2i enemyCell(static_cast<int>(getSprite().getPosition().x / Config::CELL_SIZE),
        static_cast<int>(getSprite().getPosition().y / Config::CELL_SIZE));

    // Get the target patrol point in the grid
    Vector2i targetCell(patrolPoints[currentPatrolPointIndex].x / Config::CELL_SIZE,
        patrolPoints[currentPatrolPointIndex].y / Config::CELL_SIZE);

    // Calculate the path if it's empty or if the target has changed
    if (path.empty() || path.back() != targetCell) {
        path = Pathfinding::findPath(grid, enemyCell, targetCell);
    }

    // Move the enemy to the next cell on the path if the transition delay has passed
    if (transitionClock.getElapsedTime().asSeconds() >= transitionDelay && !path.empty()) {
        Vector2i nextCell = path.front();
        Vector2f newPosition(nextCell.x * Config::CELL_SIZE, nextCell.y * Config::CELL_SIZE);
        centerOnCell(nextCell.x, nextCell.y);
        path.erase(path.begin());
        transitionClock.restart();
    }

    // Check if the enemy has reached the target patrol point
    if (path.empty() && enemyCell == targetCell) {
        // Update the patrol point index to move to the next point
        currentPatrolPointIndex = (currentPatrolPointIndex + 1) % 4;
        pauseClock.restart();

        // Recalculate the enemy's current position and the new target patrol point
        enemyCell = Vector2i(static_cast<int>(getSprite().getPosition().x / Config::CELL_SIZE),
            static_cast<int>(getSprite().getPosition().y / Config::CELL_SIZE));

        targetCell = Vector2i(patrolPoints[currentPatrolPointIndex].x / Config::CELL_SIZE,
            patrolPoints[currentPatrolPointIndex].y / Config::CELL_SIZE);

        // Calculate the new path to the next patrol point
        path = Pathfinding::findPath(grid, enemyCell, targetCell);
    }
}

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

void Enemy::setState(PatrolState newState) {
    currentState = newState;
}