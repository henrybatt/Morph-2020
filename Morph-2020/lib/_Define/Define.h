#ifndef DEFINE_H
#define DEFINE_H

#include <Arduino.h>

#define ROBOT 1


// --- Camera --- //
#define cameraSerial Serial4
#define CAM_BAUD 115200
#define CAM_PACKET_SIZE 7
#define CAM_START_BYTE 255
#define CAM_IMAGE_WIDTH 120
#define CAM_IMAGE_HEIGHT 120
#define CAM_CENTRE_X 60
#define CAM_CENTRE_Y 60
#define CAM_NO_DATA 250

// -- Bluetooth -- //
#define BT_BAUD 9600 //38400 //115200
#define BTSerial Serial5
#define BT_START_BYTE 255
#define BT_PACKET_SIZE 14
#define BT_DISCONNECT_TIME 1000000
#define BT_UPDATE_TIME 100000


#define TSSP_NO_BALL -1;

#define NO_LINE_ANGLE -1
#define NO_LINE_SIZE -1


// --- Switching --- //

// Ball must be within front of the defender and close
#define SWITCH_DEFEND_ANGLE 20
#define SWITCH_DEFEND_STRENGTH 165

// AND in front of attacker and semi far away
#define SWITCH_ATTACK_ANGLE 90
#define SWITCH_ATTACK_STRENGTH 140

// OR far from attacker
#define SWITCH_ATTACK_FAR_STRENGTH 110





#endif