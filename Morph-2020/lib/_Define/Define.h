#ifndef DEFINE_H
#define DEFINE_H

#include <Arduino.h>

#define ROBOT 1

#define CAMERA false
#define SWITCHING false

#define ACCELERATION false
#define MPU_OVERRIDE true

/* --- Orbit --- */
#define ORBIT_SURGE_SPEED 80
#define ORBIT_FAST_SPEED 60 // Vertical movement of orbit
#define ORBIT_SLOW_SPEED 40 // Horizontal movement
#define BALL_CLOSE_STRENGTH 155
#define BALL_FAR_STRENGTH 0
#define ANGLE_DIFF_MULTIPLIER 0.25
#define DIST_MULTIPLIER_1 0.02
#define DIST_MULTIPLIER_2 4.5


/* --- Acceleration --- */
#define MAX_ACCELERATION 0.5


/* --- Out Avoidance --- */
#define LINE_SIZE_BIG 0.7 // If line size bigger than move back into field
#define LINE_SIZE_MEDIUM 0.4 // If line size bigger than this decide bounce
#define LINE_SIZE_SMALL 0.1 // If line size bigger than this sit on line

#define AVOID_OVER_SPEED 90
#define AVOID_SPEED 50 // Modular speed to cross over line (1 times min, half max)
#define AVOID_BOUNCE_SPEED 40 // Modular speed to bounce over line (2 times min, 1 max)

#define AVOID_NORMAL_ANGLE 60 // Angle to move straight towards ball
#define AVOID_BOUNCE_ANGLE 150 // Angle to bounce
#define LINE_CORNER_ANGLE_THRESHOLD 30 // If angle mod 90 greater than value and less than 90 - value, must be on corner
#define LINE_BUFFER -10 //-10 // If orbit angle within line angle and buffer, must want to move outside line
#define LINE_BUFFER_CORNER -10 // ^


/* --- Attacker --- */
#define ATTACK_SURGE_STRENGTH 180 // Strength of ball to surge 
#define ATTACK_CAPTURE_ANGLE 15 // Angle range of ball to surge

// --- Defender --- //
#define DEFEND_SPEED 50
#define DEFEND_DISTANCE 74//65//60
#define DEFEND_DISTANCE_CM 25 //Distance from goal in CM to sit at

#define DEFEND_SURGE_STRENGTH 160 // Strength of ball to surge
#define DEFEND_CAPTURE_ANGLE 15 // Angle range of ball to surge

#define DEFEND_SURGE_DISTANCE 94//82//82  //70 // Distance from goal to surge till
#define DEFEND_SURGE_Y -30


/* --- Kicker --- */
#define KICKER_GOAL_ANGLE 30
#define KICKER_DISCHARGE_TIME 1000000
#define KICKER_LAST_TIMER 1000000
#define KICKER_PIN 0
#define LIGHTGATE_PIN 0
#define LIGHTGATE_THRESHOLD 0 


/* --- Motor -- */
#define MOTOR_NUM 4


/* --- Camera --- */
#define cameraSerial Serial4
#define CAM_BAUD 115200
#define CAM_PACKET_SIZE 8
#define CAM_START_BYTE 255
#define CAM_IMAGE_WIDTH 120
#define CAM_IMAGE_HEIGHT 120
#define CAM_CENTRE_X 60
#define CAM_CENTRE_Y 60
#define CAM_NO_DATA 250


/* -- Bluetooth -- */
#define BT_BAUD 9600 //38400 //115200
#define BTSerial Serial5
#define BT_START_BYTE 255
#define BT_PACKET_SIZE 16
#define BT_DISCONNECT_TIME 1000000
#define BT_UPDATE_TIME 100000


/* --- TSSPs --- */
#define TSSP_NO_BALL_ANGLE -1
#define TSSP_NO_BALL_STRENGTH 0
#define TSSP_NUM 18
#define TSSP_NUM_MULTIPLIER 20 //360 / LS_NUM
#define TSSP_READ_NUM 255
#define TSSP_PERIOD 4


/* --- Light Sensors --- */
#define LS_NUM 32
#define LS_NUM_MULTIPLIER 11.25 // 360 / LS_NUM
#define NO_LINE_ANGLE -1
#define NO_LINE_SIZE 0
#define NO_LINE_STATE 0
#define LS_CALIBRATION_COUNT 50
#define LS_CALIBRATION_BUFFER 300


/* --- Switching --- */
#define SWITCH_TIMER 2000000
// Ball must be within front of the defender and close
#define SWITCH_DEFEND_ANGLE 20
#define SWITCH_DEFEND_STRENGTH 165

// AND in front of attacker and semi far away
#define SWITCH_ATTACK_ANGLE 90
#define SWITCH_ATTACK_STRENGTH 140

// OR far from attacker
#define SWITCH_ATTACK_FAR_STRENGTH 110


/* --- Role LED Timers --- */
#define ATTACK_LED 500000
#define DEFEND_LED 1000000
#define UNDECIDED_LED 200000


/* --- MPU Sensor --- */
#define MPU_CALIBRATION_COUNT 20
#define MPU_CALIBRATION_TIME 50
#define MPU9250_ADDRESS 0x68
#define MAG_ADDRESS 0x0C
#define GYRO_FULL_SCALE_250_DPS 0x00
#define GYRO_FULL_SCALE_500_DPS 0x08
#define GYRO_FULL_SCALE_1000_DPS 0x10
#define GYRO_FULL_SCALE_2000_DPS 0x18
#define ACC_FULL_SCALE_2_G 0x00
#define ACC_FULL_SCALE_4_G 0x08
#define ACC_FULL_SCALE_8_G 0x10
#define ACC_FULL_SCALE_16_G 0x18


/* --- Field Information --- */
#define FIELD_WIDTH_CM 182
#define FIELD_LENGTH_CM 243
#define GOAL_OFFSET_CM 30
#define DEFENDING_BOX_WIDTH_CM 30
#define FIELD_LENGTH_WITH_GOAL (FIELD_LENGTH_CM/2 - GOAL_OFFSET_CM)


/* --- Coords --- */
#define COORD_THRESHOLD_DISTANCE 2

//Coords to move when no ball visible
#define NO_BALL_COORD_X 0
#define NO_BALL_COORD_Y 0

//Coords to move when other robot sees ball is out of field
#define BALL_OUT_COORD_X 0
#define BALL_OUT_COORD_Y -30

#define NEW_COORD_TIMER 250000


/* --- Screen --- */

// TS Values
#define TS_MINX 150
#define TS_MINY 130
#define TS_MAXX 3800
#define TS_MAXY 4000

// Min and max pressure values to be considered a touch
#define MIN_PRESSURE 100
#define MAX_PRESSURE 1300

// Common colours as hex values
#define BLACK 0x0000
#define NAVY 0x000F
#define DARKGREEN 0x03E0
#define DARKCYAN 0x03EF
#define MAROON 0x7800
#define PURPLE 0x780F
#define OLIVE 0x7BE0
#define LIGHTGREY 0xC618
#define DARKGREY 0x7BEF
#define BLUE 0x001F
#define GREEN 0x07E0
#define CYAN 0x07FF
#define RED 0xF800
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF
#define ORANGE 0xFD20
#define GREENYELLOW 0xAFE5
#define PINK 0xF81F
#define DIMGREY 0x6B4D
#define DEEPBLUE 0x000B

#define BACKGROUND_COLOUR BLACK
#define FOREGROUND_COLOUR LIGHTGREY
#define HIGHLIGHT_COLOUR BLUE

#define TFT_ROTATION 1

#endif