#ifndef FSM_HPP
#define FSM_HPP

#include <iostream>
#include <cmath>
#include "src/map/Grid.hpp"
#include "src/entities/Player.hpp"

using namespace std;

class FSM {
public:
	enum State {
		PATROL,
		CHASE,
		RETURN
	};
	State currentState;

	bool detectPlayer(Player& player);

	void update(Player& player, Grid& grid, float deltaTime);


};


#endif