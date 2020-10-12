#include "States.h"
#include "StatesMovement.h"

using namespace States::Global;
using namespace States::Timers;


Kick States::Global::kick = Kick();

void States::timer_manager() {
    kickerTimer->Update();

    if (robotState.isAttack) {
        if (robotState.ball.visible()) {
            attackIdleTimer->Stop();
        }
        attackIdleTimer->Update();
    }
}

bool States::canKick = true;

Timer *States::Timers::attackIdleTimer = new Timer(IDLE_TIMEOUT, &attack_idle_timer_callback);
void States::Timers::attack_idle_timer_callback() {
    attackIdleTimer->Stop();
    SM_CHANGE_STATE_ATTACK(idle);
}

Timer *States::Timers::kickerTimer = new Timer(KICKER_TIMEOUT, &kicker_timer_callback);
void States::Timers::kicker_timer_callback() {
    kickerTimer->Stop();
    canKick = true;
}


/* -- Global Kick State -- */

Kick::Kick() {
    name = "Global Kick";
}

void Kick::update() {
    canKick = false;
    kickerTimer->Resume();

    // Insert kicker code
}
