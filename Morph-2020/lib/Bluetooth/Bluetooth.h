#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <Arduino.h>
#include <Common.h>

#include <BluetoothData.h>

#include <Timer.h>

class Bluetooth{

    public:

        /* -- Setup Bluetooth -- */
        void init();

        /* -- Update Data and send + recieve -- */
        void update(Role *role, BluetoothData data);

        bool isConnected;

        bool previouslyConnected;

        BluetoothData otherData = BluetoothData();

    private:

        void send();

        void recieve();

        void updateRole(Role *role);

        bool shouldSwitch(BluetoothData attacker, BluetoothData defender);

        BluetoothData thisData = BluetoothData();

        Timer disconnectTimer = Timer(BT_DISCONNECT_TIME);

        Role defaultRole = ROBOT ? Role::defend : Role::attack;

};



#endif