#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Entity.hpp"
#include "Player.hpp"
#include "../ia/goap/State.hpp"

class Enemy : public Entity {
public:
    Player* p;

    static constexpr float SPEED = 100.0f;
    static constexpr float DETECTION_RADIUS = 300.0f;

    Enemy(float x, float y, int hp);
    void update(float deltaTime, Grid& grid, vector<Entity*> players) override;
    void FSM(Player& player, vector<Entity*> players, float deltaTime, Grid& grid);
    void detectPlayer(Player& player, Grid& grid, float deltaTime);
    void returnPos(Player& player, Grid& grid, float deltaTime);
    
    enum State {PATROL, CHASE, RETURN};
    State currentState;

private:

    void executeGoapAction(const std::string& actionName, float deltaTime, Grid& grid, Player* player);
    void chase(Player& player, float deltaTime, Grid& grid);
    void patrol();
    void flee(Player& player, float deltaTime, Grid& grid);

    //State state;
};

#endif // ENEMY_HPP