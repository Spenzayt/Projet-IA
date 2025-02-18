#include "Enemy.hpp"
#include "Player.hpp"

#include <cmath>
#include <iostream>

using namespace std;

Enemy::Enemy(float x, float y) : Entity(x, y, Color::Red) /*State(make_unique<IdleState>())*/ {}

void Enemy::setState(unique_ptr<State> newState) {
	state = move(newState);
}

void Enemy::update(float deltaTime, Grid& grid) {
	state->handle(*this);
}

void Enemy::forceState(unique_ptr<State> newState) {
	cout << "GOAP force l'état : " << newState->getName() << endl;
	setState(move(newState));

}

string Enemy::getCurrentState() const { return state->getName(); }