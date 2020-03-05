#ifndef DEFINE_H
#define DEFINE_H

#include <Arduino.h>

#define ROBOT 1 // Robot 1 or 0



/* --- Slave + Serial --- */
#define SLAVE_SERIAL Serial1
#define MASTER_SERIAL Serial1
#define TEENSY_BAUD 9600
#define SLAVE_PACKET_SIZE 10
#define SLAVE_START_BYTE 255

/* --- TSSP Sensors --- */
#define TSSP_NUM 18 // Number of TSSPS
#define TSSP_NUM_MULTIPLIER 20 // Angle between TSPPS - 360/num
#define TSSP_NUM_CAL 4 // Number of sensors used to calculate values
#define TSSP_NO_BALL_ANGLE -1 // Default no ball value
#define TSSP_NO_BALL_STRENGTH 0 // Default no ball value
#define TSSP_PERIOD_NUM 4 // Number of periods in a sensor read
#define TSSP_PERIOD_TIME 833 // Number of micro seconds per ball cylce


/* --- Light Sensors --- */
#define LS_NUM 32 // Number of LS
#define LS_NUM_MULTIPLIER 11.25  // Angle between LS - 360/num
#define NO_LINE_ANGLE -1 // Default no line angle
#define NO_LINE_SIZE 0 // Default no line size
#define LS_CALIBRATION_COUNT 50 // Number of LS calibrations
#define LS_CALIBRATION_BUFFER 300 // Calibration buffer


/* --- Out Avoidance --- */
#define LINE_SIZE_BIG 0.7     // If line size bigger than move back into field
#define LINE_SIZE_MEDIUM 0.4  // If line size bigger than this decide bounce
#define LINE_SIZE_SMALL 0.1   // If line size bigger than this sit on line

#define AVOID_OVER_SPEED 90
#define AVOID_SPEED 50         // Modular speed to cross over line (1 times min, half max)
#define AVOID_BOUNCE_SPEED 40  // Modular speed to bounce over line (2 times min, 1 max)

#define AVOID_NORMAL_ANGLE 60           // Angle to move straight towards ball
#define AVOID_BOUNCE_ANGLE 150          // Angle to bounce
#define LINE_CORNER_ANGLE_THRESHOLD 30  // If angle mod 90 greater than value and less than 90 - value, must be on corner
#define LINE_BUFFER -10                 //-10 // If orbit angle within line angle and buffer, must want to move outside line
#define LINE_BUFFER_CORNER -10          // ^


/* --- Orbit --- */
/* --- Orbit --- */
#define ORBIT_SURGE_SPEED 80
#define ORBIT_FAST_SPEED 60  // Vertical movement of orbit
#define ORBIT_SLOW_SPEED 40  // Horizontal movement
#define BALL_CLOSE_STRENGTH 155
#define BALL_FAR_STRENGTH 0
#define ANGLE_DIFF_MULTIPLIER 0.25
#define DIST_MULTIPLIER_1 0.02
#define DIST_MULTIPLIER_2 4.5


/* --- Movement --- */
#define NO_ANGLE 0
#define NO_SPEED 0
#define NO_CORRECTION 127


/* --- Position --- */
#define NO_VECTOR 127

#endif

