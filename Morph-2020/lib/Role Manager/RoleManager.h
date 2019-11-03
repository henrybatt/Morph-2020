#ifndef ROLEMANAGER_H
#define ROLEMANAGER_H

#include <Arduino.h>
#include <Common.h>

#include <Timer.h>

#include <RoleData.h>

#include <Bluetooth.h>

class RoleManager{

    public:

        /* -- Class Constructor + Init -- */
        RoleManager();

        /* -- Update current role and handles switching -- */
        void update();

        /* -- Request to switch roles --- */
        void requestSwitch();

        /* -- If switch timer is still active -- */
        bool hasSwitched();

        /* -- Is requesting to switch -- */
        bool isSwitching();

        /* -- Returns current role or if not one pick default -- */
        Role getRole();

         /* -- Flash LED based off set role -- */
        void roleLED();


    private:

        /* -- Control for if they should switch -- */
        void masterSwitch();

        /* -- Pick opposite role of other robot -- */
        void pickOpposite();

        /* -- Role undecided, determine starting role -- */
        void undecidedRole();

        /* -- Decides to switch -- */
        bool shouldSwitch();

        bool requestingSwitch;

        bool isMaster; // Is incharge of switch handling

        bool ledOn; // LED State

        Role defaultRole = Role::undecided;
        Role currentRole = Role::undecided;
        Role otherPreviousRole = Role::undecided;

        Timer switchTimer = Timer(SWITCH_TIMER);

        Timer attackLEDTimer = Timer(ATTACK_LED);
        Timer defendLEDTimer = Timer(DEFEND_LED);
        Timer undecidedLEDTimer = Timer(UNDECIDED_LED);

};

extern RoleManager roleManager;

#endif
