#ifndef WORLDSTATE_HPP
#define WORLDSTATE_HPP

#include <SFML/Graphics.hpp>
#include <string>

using namespace std;
using namespace sf;

class WorldState {
public:
    bool hasFood;
    bool hasWater;
    int hunger;
    int thirst;

    WorldState(bool food = false, bool water = false, int hungerValue = 100, int thirstValue = 100)
        : hasFood(food), hasWater(water), hunger(hungerValue), thirst(thirstValue) {
    }

    bool HasFood() const { return hasFood; }
    bool HasWater() const { return hasWater; }
    int GetHunger() const { return hunger; }
    int GetThirst() const { return thirst; }

    void SetFood(bool food) { hasFood = food; }
    void SetWater(bool water) { hasWater = water; }

    void ReduceHunger() { hunger = max(0, hunger - 50); }
    void ReduceThirst() { thirst = max(0, thirst - 50); }

    bool IsInGoodCondition() const {
        return hunger < 50 && thirst < 50;
    }
};

#endif // WORLDSTATE_HPP