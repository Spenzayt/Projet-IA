#ifndef STATE_HPP
#define STATE_HPP

#include <algorithm>
#include <iostream>
#include <memory>
#include <string>

using namespace std;

class Enemy;

class State {
public:
    bool isLow = false;
    bool hasSeenPlayer = false;

    State(bool lowStatus = false, bool seenStatus = false)
        : isLow(lowStatus), hasSeenPlayer(seenStatus) {
    }

    bool IsLow() const { return isLow; }
    bool HasSeenPlayer() const { return hasSeenPlayer; }

    void SetLow(bool lowStatus) { isLow = lowStatus; }
    void SetSeenPlayer(bool seenStatus) { hasSeenPlayer = seenStatus; }
};

#endif // STATE_HPP