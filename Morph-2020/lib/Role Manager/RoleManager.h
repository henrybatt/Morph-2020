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

        /* -- Flash LED based off set role -- */
        void roleLED();

        /* -- Returns current role or if not one pick default -- */
        Role getRole();

    private:

        /* -- Decides to switch -- */
        bool shouldSwitch(BluetoothData attacker, BluetoothData defender);

        bool ledOn; // LED State

        Role defaultRole = Role::undecided;
        Role currentRole = Role::undecided;

        Timer attackLEDTimer = Timer(ATTACK_LED);
        Timer defendLEDTimer = Timer(DEFEND_LED);
        Timer undecidedLEDTimer = Timer(UNDECIDED_LED);

};

extern RoleManager roleManager;

#endif
