
#ifndef STATES_H
#define STATES_H

#include <Arduino.h>
#include "Common.h"
#include "StateMachine.h"
#include "RobotState.h"
#include "Timer.h"

namespace States{

    extern bool canKick;
    extern void timer_manager();

    namespace Attack{

        class Idle : public State{
            public:
                Idle();
                void update();
        };

        class Orbit : public State{
            public:
                Orbit();
                void update();
        };

        class BallHandle : public State{
            public: 
                BallHandle();
                void enter();
                void update();
            private:
                float accelProg;
                float accelStart;
        };

        extern Idle idle;
        extern Orbit orbit;
        extern BallHandle ballHandle;
    }

    namespace Defence{

        class Idle : public State {
            public:
                Idle();
                void update();
        };

        class Defend : public State {
            public:
                Defend();
                void update();
        };

        class Search : public State {
            public:
                Search();
                void update();
        };

        class Surge : public State {
            public:
                Surge();
                void enter();
                void update();
                float accelProg;
        };

        extern Idle idle;
        extern Defend defend;
        extern Search search;
        extern Surge surge;
    }

    namespace Global{
        class Kick : public State{
            public:
                Kick();
                void update();
        };

        extern Kick kick;
    }

    namespace Timers{

        extern Timer *kickerTimer;
        extern void kicker_timer_callback();

        extern Timer *attackIdleTimer;
        extern void attack_idle_timer_callback();
    }

}



#endif