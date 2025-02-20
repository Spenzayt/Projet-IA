#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Entity.hpp"
#include "Player.hpp"
#include "../ia/goap/State.hpp"
#include "../ia/pathfinding/Pathfinding.hpp"
#include <cmath>
#include <iostream>

class Player;

enum class PatrolState {
    Patrolling,
    Paused,
    Alerted
};

class Enemy : public Entity {
public:
    static constexpr float SPEED = 100.0f;
    static constexpr float DETECTION_RADIUS = 300.f;

    Enemy(float x, float y, int hp);
    void update(float deltaTime, Grid& grid, vector<Entity*>& players) override;
    void draw(RenderWindow& window) override;

private:
    void executeGoapAction(const string& actionName, float deltaTime, Grid& grid, Player* player);
    void chase(Player& player, float deltaTime, Grid& grid);
    void patrol(float deltaTime, Grid& grid);
    void flee(Player& player, float deltaTime, Grid& grid);
    void setState(PatrolState newState);

    State state;
    vector<Vector2i> path;

    PatrolState currentState;
    Vector2i patrolPoints[4];
    int currentPatrolPointIndex;
    sf::Clock pauseClock;
    float pauseDuration;
};

#endif // ENEMY_HPP