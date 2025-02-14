#ifndef PLANNER_HPP
#define PLANNER_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "Action.hpp"
#include "Goal.hpp"
#include "WorldState.hpp"

class Planner {
public:
    vector<Action*> actions;
    vector<Goal*> goals;

    Planner() {}

    void Plan(const Goal& goal, const WorldState& currentState) {
        for (auto action : actions) {
            if (action->IsAchievable(currentState)) {
                action->Execute();
                break;
            }
        }
    }

    void AddAction(Action* action) {
        actions.push_back(action);
    }

    void AddGoal(Goal* goal) {
        goals.push_back(goal);
    }
};

#endif // PLANNER_HPP