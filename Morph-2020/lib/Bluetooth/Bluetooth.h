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

        /* -- Currently connected to bluetooth -- */
        bool isConnected;

        /* -- Has been connected at some point -- */
        bool previouslyConnected;

        /* -- Return robot's bluetooth data -- */
        BluetoothData getThisData();
        BluetoothData getOtherData();

        /* -- Robot data structures -- */
        BluetoothData thisData = BluetoothData();
        BluetoothData otherData = BluetoothData();

    private:

        /* -- Send new data -- */
        void send();

        /* -- Recieve other data -- */
        void recieve();

        /* -- Disconnect timer -- */
        Timer disconnectTimer = Timer(BT_DISCONNECT_TIME);

};

extern Bluetooth bluetooth;

#endif