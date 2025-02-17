#include "GOAPAgent.hpp"

GOAPAgent::GOAPAgent() {}

void GOAPAgent::PerformActions() {
    Goal goal;

    if (state.IsLow()) {
        goal = Goal::Flee;
    }
    else if (state.HasSeenPlayer()) {
        goal = Goal::Chasing;
    }
    else {
        goal = Goal::Patrolling;
    }

    vector<std::unique_ptr<Action>> plan = planner.Plan(state, goal);

    for (auto& action : plan) {
        if (action->CanExecute(state)) {
            action->Execute(state);
        }
        else {
            cout << "Action impossible : " << typeid(*action).name() << "\n";
        }
    }
}

void GOAPAgent::PrintState() {
    cout << "Enemy State: \n";
    cout << "Has seen player: " << (state.HasSeenPlayer() ? "Yes" : "No") << "\n";
    cout << "Is low (fleeing): " << (state.IsLow() ? "Yes" : "No") << "\n";
}