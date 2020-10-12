
#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <Arduino.h>
#include "Common.h"
#include <String>
#include <vector>

struct State{
    State();
    State(String name);
    virtual void enter();
    virtual void update();
    virtual void exit();
    String name;
};

class StateMachine{

    public:
        StateMachine();
        StateMachine(State *beginningState);

        void update();

        void change_state(State *new_state);

        void revert_state();

        String get_current_state_name();

    private:

        void push_to_state_history(State *current_state);

        State *current_state;
        std::vector<State*> state_history;


};

extern StateMachine sm;

#endif