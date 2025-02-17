#include "GOAPPlanner.hpp"

vector<std::unique_ptr<Action>> GOAPPlanner::Plan(const State& initialState, Goal goal) {
    vector<std::unique_ptr<Action>> plan;

    if (initialState.HasSeenPlayer()) {
        goal = Goal::Chasing;
    }

    if (initialState.IsLow()) {
        goal = Goal::Flee;
    }

    switch (goal) {
    case Goal::Patrolling:
        plan.push_back(make_unique<PatrolAction>());
        break;

    case Goal::Chasing:
        plan.push_back(make_unique<ChaseAction>());
        break;

    case Goal::Flee:
        plan.push_back(make_unique<FleeAction>());
        break;

    default:
        break;
    }

    return plan;
}
