#include "StateMachine.h"

/* -- Genertic State Setup -- */
State::State(){}
State::State(String name) : name(name){}
void State::enter(){}
void State::update(){}
void State::exit(){}

StateMachine::StateMachine(){
    current_state = new State();
}

StateMachine::StateMachine(State *beginning_state){
    current_state = new State();
    change_state(beginning_state);
}

void StateMachine::update(){
    current_state->update();
}

void StateMachine::change_state(State *new_state){

    if (current_state == new_state){ return; }

    push_to_state_history(current_state);

    current_state->exit();
    current_state = new_state;
    current_state->enter();
}

void StateMachine::revert_state(){
    if (state_history.size() >= 1){
        State *previous_state = state_history.back();
        state_history.pop_back();

        current_state->exit();
        current_state = previous_state;
        current_state->enter();
    }
}

String StateMachine::get_current_state_name(){
    return current_state->name;
}

void StateMachine::push_to_state_history(State *current_state){
    if (state_history.size() >= 256){
        State *last_state = state_history.back();
        State *second_last_state = state_history.at(state_history.size()-2);

        state_history.clear();

        state_history.push_back(second_last_state);
        state_history.push_back(last_state);
    }
    state_history.push_back(current_state);
}


