#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <stdint.h>

#define EN_L_PIN 5
#define IN4_L_PIN 3
#define IN3_L_PIN 4
#define IN2_P_PIN 8
#define IN1_P_PIN 9
#define EN_P_PIN 6

#define SENS_L_2 A5
#define SENS_L_1 A4
#define SENS_P_1 A3
#define SENS_P_2 A2

#define OPTION_POT A1
#define BUTTON_START_PIN 2
#define BUTTON_STOP_PIN 7

enum Maneuver {GO_STRAIGHT, TURN_LEFT, TURN_RIGHT, REVERSE, STOP};

enum Robot_State {EXECUTING_PATH, STAND_BY};

#define MAX_PATH_SIZE 15

#endif
