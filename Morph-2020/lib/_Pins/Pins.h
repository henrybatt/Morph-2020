#ifndef PINS_H
#define PINS_H

#include <Arduino.h>


/* --- Light Sensors --- */

#define MUX_A_OUT A11
#define MUX_A_0 50
#define MUX_A_1 51
#define MUX_A_2 52
#define MUX_A_3 53

#define MUX_B_OUT A10
#define MUX_B_0 57
#define MUX_B_1 56
#define MUX_B_2 55
#define MUX_B_3 54

#define LS_1 7
#define LS_2 6
#define LS_3 5
#define LS_4 4
#define LS_5 3
#define LS_6 2
#define LS_7 1
#define LS_8 0
#define LS_9 8
#define LS_10 9
#define LS_11 10
#define LS_12 11
#define LS_13 12
#define LS_14 13
#define LS_15 14
#define LS_16 15
#define LS_17 23
#define LS_18 22
#define LS_19 21
#define LS_20 20
#define LS_21 19
#define LS_22 18
#define LS_23 17
#define LS_24 16
#define LS_25 24
#define LS_26 25
#define LS_27 26
#define LS_28 27
#define LS_29 28
#define LS_30 29
#define LS_31 30
#define LS_32 31


/* --- TSSPs --- */
#define TSSP_PIN_1 24
#define TSSP_PIN_2 14
#define TSSP_PIN_3 15
#define TSSP_PIN_4 16
#define TSSP_PIN_5 17
#define TSSP_PIN_6 20
#define TSSP_PIN_7 25
#define TSSP_PIN_8 12
#define TSSP_PIN_9 11
#define TSSP_PIN_10 3
#define TSSP_PIN_11 40
#define TSSP_PIN_12 41
#define TSSP_PIN_13 42
#define TSSP_PIN_14 43
#define TSSP_PIN_15 44
#define TSSP_PIN_16 49
#define TSSP_PIN_17 38
#define TSSP_PIN_18 39


/* --- Motors --- */

// Front Right
#define MOTOR_FRONT_RIGHT_ENA 37
#define MOTOR_FRONT_RIGHT_IN1 35
#define MOTOR_FRONT_RIGHT_IN2 36
#define MOTOR_FRONT_RIGHT_ANGLE 45
#define MOTOR_FRONT_RIGHT_REVERSED false

// Back Right
#define MOTOR_BACK_RIGHT_ENA 23
#define MOTOR_BACK_RIGHT_IN1 21
#define MOTOR_BACK_RIGHT_IN2 22
#define MOTOR_BACK_RIGHT_ANGLE 135
#define MOTOR_BACK_RIGHT_REVERSED false

// Back Left
#define MOTOR_BACK_LEFT_ENA 4
#define MOTOR_BACK_LEFT_IN1 5
#define MOTOR_BACK_LEFT_IN2 6
#define MOTOR_BACK_LEFT_ANGLE 225
#define MOTOR_BACK_LEFT_REVERSED false

// Front Left
#define MOTOR_FRONT_LEFT_ENA 29
#define MOTOR_FRONT_LEFT_IN1 27
#define MOTOR_FRONT_LEFT_IN2 28
#define MOTOR_FRONT_LEFT_ANGLE 315
#define MOTOR_FRONT_LEFT_REVERSED false


/* -- Screen -- */

#define TFT_DC 9
#define TFT_CS 10
#define TFT_RST 255 // 255 = unused, connect to 3.3V
#define TFT_MOSI 11
#define TFT_SCLK 13
#define TFT_MISO 12

#define STMPE_CS 8

#endif