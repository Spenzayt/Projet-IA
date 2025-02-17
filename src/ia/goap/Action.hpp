#ifndef ACTION_HPP
#define ACTION_HPP

#include "State.hpp"
#include <iostream>

class Action {
public:
    virtual bool CanExecute(const State& state) const = 0;
    virtual void Execute(State& state) = 0;
    virtual ~Action() {}
};

class PatrolAction : public Action {
public:
    bool CanExecute(const State& state) const override {
        return !state.IsLow() && !state.HasSeenPlayer();
    }

    void Execute(State& state) override {}
};

class ChaseAction : public Action {
public:
    bool CanExecute(const State& state) const override {
        return !state.IsLow() && state.HasSeenPlayer();
    }

    void Execute(State& state) override {}
};

class FleeAction : public Action {
public:
    bool CanExecute(const State& state) const override {
        return state.IsLow() && state.HasSeenPlayer();
    }

    void Execute(State& state) override {}
};

#endif // ACTION_HPP