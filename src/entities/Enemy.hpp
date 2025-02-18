#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Entity.hpp"
#include "State.hpp"

#include <memory>
#include <vector>


class Enemy : public Entity {
private:
    unique_ptr<State>state;
public:

    static constexpr float SPEED = 100.0f;

    Enemy(float x, float y);
    void update(float deltaTime, Grid& grid) override;

    void setState(unique_ptr<State> newState);
    void forceState(unique_ptr<State> newState);

    string getCurrentState() const;
};

#endif // ENEMY_HPP