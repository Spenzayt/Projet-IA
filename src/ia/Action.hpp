#ifndef ACTION_HPP
#define ACTION_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include "WorldState.hpp"

class Action {
public:
    string name;

    Action(const string& actionName) : name(actionName) {}

    virtual void Execute() = 0;
    virtual bool IsAchievable(const WorldState& state) const = 0;
};

#endif // ACTION_HPP