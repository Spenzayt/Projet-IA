#include "Planner.hpp"
#include <queue>
#include <iostream>

std::vector<Action*> Planner::plan(Goal& goal, const WorldState& currentWorldState, const std::vector<Action*>& actions) {
    return generatePlan(goal, currentWorldState, actions);
}

std::vector<Action*> Planner::generatePlan(Goal& goal, const WorldState& currentWorldState, const std::vector<Action*>& actions) {
    std::vector<Action*> plan;

    for (auto& action : actions) {
        if (action->checkPreconditions(currentWorldState)) {
            plan.push_back(action);
        }
    }

    if (goal.isAchieved(currentWorldState)) {
        std::cout << "Goal achieved!" << std::endl;
    }
    else {
        std::cout << "Goal not achieved yet." << std::endl;
    }

    return plan;
}