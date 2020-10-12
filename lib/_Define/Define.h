#ifndef DEFINE_H
#define DEFINE_H


#include <Arduino.h>

#define ROBOT 1 // Robot 1 or 0


#define CAMERA true
#define SWITCHING true
#define ACCELERATION false

/* --- Slave + Serial --- */
#define SLAVE_SERIAL Serial1
#define MASTER_SERIAL Serial1
#define TEENSY_BAUD 9600
#define SLAVE_PACKET_SIZE 10
#define SLAVE_START_BYTE 255
#define SLAVE_LED_DURATION 100 // In milliseconds

/* --- TSSP Sensors --- */
#define TSSP_NUM 18 // Number of TSSPS
#define TSSP_NUM_MULTIPLIER 20 // Angle between TSPPS - 360/num
#define TSSP_NUM_CAL 4 // Number of sensors used to calculate values
#define TSSP_NO_BALL_ANGLE 0 // Default no ball value
#define TSSP_NO_BALL_STRENGTH 0 // Default no ball value
#define TSSP_PERIOD_NUM 4 // Number of periods in a sensor read
#define TSSP_PERIOD_TIME 833 // Number of micro seconds per ball cylce


/* --- Light Sensors --- */
#define LS_NUM 32 // Number of LS
#define LS_NUM_MULTIPLIER 11.25  // Angle between LS - 360/num
#define NO_LINE_ANGLE -1 // Default no line angle
#define NO_LINE_SIZE 0 // Default no line size
#define LS_CALIBRATION_COUNT 50 // Number of LS calibrations
#define LS_CALIBRATION_BUFFER 200 // Calibration buffer


/* --- Out Avoidance --- */
#define LINE_SIZE_BIG 1.5     // If line size bigger then move back into field
#define LINE_SIZE_SMALL 0.1   // If line size smaller then ignore

#define AVOID_OVER_SPEED 80
#define AVOID_SPEED 40         // Modular speed to cross over line

#define AVOID_NORMAL_ANGLE 60           // Max angle to move straight towards ball
#define AVOID_PURSUE_ANGLE 150           // Angle to pursue (180 - angle to exclude)
#define LINE_CORNER_ANGLE_THRESHOLD 30  // If angle mod 90 greater than value and less than 90 - value, must be on corner
#define LINE_BUFFER -10                 //-10 // If orbit angle within line angle and buffer, must want to move outside line
#define LINE_BUFFER_CORNER -10          // ^

/* --- Lightgate --- */
#define LIGHTGATE_PIN A0
#define LIGHTGATE_THRESHOLD 100

/* --- Kicker --- */
#define KICKER_TIMEOUT 1000 // Time until next kick

/* --- Motor + Acceleration-- */
#define MOTOR_NUM 4
#define MAX_ACCELERATION 0.5

/* --- Orbit --- */
#define ORBIT_SURGE_SPEED 80 // Speed to surge when ball is in front
#define ORBIT_FAST_SPEED 60  // Vertical movement of orbit
#define ORBIT_SLOW_SPEED 42  // Horizontal movement
#define BALL_CLOSE_STRENGTH 160//180
#define BALL_FAR_STRENGTH 30//0
#define ANGLE_DIFF_MULTIPLIER 0.15//0.25
#define DIST_MULTIPLIER_1 0.02
#define DIST_MULTIPLIER_2 4.5


/* --- MPU Sensor --- */
#define MPU_CALIBRATION_COUNT 30
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

/* --- Attacker --- */
#define IDLE_TIMEOUT 2000 // ms Time before switch to idle 
#define ATTACK_SURGE_STRENGTH 180   // Strength of ball to surge
#define ATTACK_CAPTURE_ANGLE 15     // Angle range of ball to surge
#define ATTACK_CORRECT_ANGLE 60     // Angle range of ball infront to goal correct
#define DOUBLE_DEF_MIN_J -30        // Minimum J value when avoiding double defence
#define ATTACK_LERP_ACCEL_PROG 0.05 // Number of ticks to reach max speed - (1/LERP_ACCEL_PROG)

/* --- Defender --- */
#define DEFENCE_KICK_TIMOUT 500 // ms Time to surge before kicking
#define DEFEND_DISTANCE_CM 25  //Distance from goal in CM to sit at

#define DEFEND_SURGE_STRENGTH 160  // Strength of ball to surge
#define DEFEND_CAPTURE_ANGLE 15    // Angle range of ball to surge
#define DEFEND_SURGE_J -30      // Distance from goal to surge till
#define DEFEND_ANGLE 90         // Angle range of ball to defend
#define DEFEND_SEARCH_REVERSE -15 // Rate at which we reverse to find goal
#define DEFEND_LERP_ACCEL_PROG 0.005  // Number of ticks to reach max speed - (1/LERP_ACCEL_PROG)

/* --- Camera --- */
#define CAM_SERIAL Serial4
#define CAM_BAUD 115200
#define CAM_PACKET_SIZE 8
#define CAM_START_BYTE 255


/* --- Movement --- */
#define NO_ANGLE 0
#define NO_SPEED 0
#define NO_CORRECTION 0


/* --- Position --- */
#define NO_POSTION 127


/* --- Coords --- */
#define COORD_THRESHOLD_DISTANCE 2

#define IDLE_COORD_I 0  //Coords to move when no ball visible
#define IDLE_COORD_J -20

#define BALL_OUT_COORD_I 0  //Coords to move when other robot sees ball is out of field
#define BALL_OUT_COORD_J -30


// --- Field Information --- //
#define FIELD_WIDTH_CM 182
#define FIELD_LENGTH_CM 243
#define GOAL_OFFSET_CM 30
#define DEFENDING_BOX_WIDTH_CM 30
#define FIELD_LENGTH_WITH_GOAL (FIELD_LENGTH_CM / 2 - GOAL_OFFSET_CM)
#define ATTACK_GOAL_J  (FIELD_LENGTH_CM / 2 - GOAL_OFFSET_CM)
#define DEFEND_GOAL_J -(FIELD_LENGTH_CM / 2 + GOAL_OFFSET_CM)

/* --- PIDs --- */

/* - Default Heading Correction PID - */
#define HEADING_KP 1
#define HEADING_KI 0
#define HEADING_KD 0.1
#define HEADING_MAX_CORRECTION 100

/* - Idle Correction PID - */
#define IDLE_KP 1
#define IDLE_KI 0
#define IDLE_KD 0.1
#define IDLE_MAX_CORRECTION 100

/* - Goal PIDs - */
#define GOAL_ATTACK_KP 0
#define GOAL_ATTACK_KI 0
#define GOAL_ATTACK_KD 0
#define GOAL_ATTACK_MAX_CORRECTION 100

#define GOAL_DEFEND_KP 0
#define GOAL_DEFEND_KI 0
#define GOAL_DEFEND_KD 0
#define GOAL_DEFEND_MAX_CORRECTION 100

/* - Coord PIDs - */
#define I_MOVEMENT_KP 0
#define I_MOVEMENT_KI 0
#define I_MOVEMENT_KD 0
#define I_MOVEMENT_MAX_SPEED 100

#define J_MOVEMENT_KP 0
#define J_MOVEMENT_KI 0
#define J_MOVEMENT_KD 0
#define J_MOVEMENT_MAX_SPEED 100

#define TO_COORD_KP 0
#define TO_COORD_KI 0
#define TO_COORD_KD 0
#define TO_COORD_MAX_SPEED 100

#endif

