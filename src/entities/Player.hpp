#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Entity.hpp"
#include "Enemy.hpp"
#include "../game/Config.hpp"
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <vector>

class Player : public Entity {
public:
    static constexpr int DAMAGE = 20;
    static constexpr float ATTACK_COOLDOWN = 0.5f;

    Player(float x, float y, int hp);

    void attack(vector<Entity*>& enemies);
    void update(float deltaTime, Grid& grid, vector<Entity*>& enemies) override;
    void draw(RenderWindow& window) override;

private:
    float attackTimer = 0.f;
    float moveTimer = 0.f;
    static constexpr float moveDelay = 0.05f;
};

#endif // PLAYER_HPP