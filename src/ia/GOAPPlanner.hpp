#ifndef GOAPPLANNER_HPP
#define GOAPPLANNER_HPP

#include "Action.hpp"
#include <vector>
#include <memory>

enum class Goal {
    Patrolling,
    Chasing,
    Flee
};

class GOAPPlanner {
public:
    vector<std::unique_ptr<Action>> Plan(const State& initialState, Goal goal);
};

#endif // GOAPPLANNER_HPP