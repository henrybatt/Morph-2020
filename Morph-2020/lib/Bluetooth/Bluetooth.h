#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <Arduino.h>
#include <Common.h>

#include <BluetoothData.h>
#include <Timer.h>

class Bluetooth{

    public:

        /* -- Class Constructor + Init -- */
        Bluetooth();

        /* -- Update Data and send + recieve -- */
        void update(BluetoothData data);

        bool isConnected;

        bool previouslyConnected;

        BluetoothData thisData = BluetoothData();
        BluetoothData otherData = BluetoothData();

    private:

        void send();

        void recieve();

        Timer disconnectTimer = Timer(BT_DISCONNECT_TIME);

};

extern Bluetooth bluetooth;

#endif