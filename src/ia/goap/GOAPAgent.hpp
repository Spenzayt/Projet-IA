#ifndef GOAPAGENT_HPP
#define GOAPAGENT_HPP

#include "State.hpp"
#include "GOAPPlanner.hpp"
#include <iostream>

class GOAPAgent {
private:
    State state;
    GOAPPlanner planner;

public:
    GOAPAgent();
    void PerformActions();
    void PrintState();
};

#endif // GOAPAGENT_HPP