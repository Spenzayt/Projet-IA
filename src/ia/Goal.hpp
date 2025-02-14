#ifndef GOAL_HPP
#define GOAL_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include "WorldState.hpp"

class Goal {
public:
    string goalName;

    Goal(const string& goal) : goalName(goal) {}

    virtual bool IsAchieved(const WorldState& state) const = 0;
};

#endif // GOAL_HPP