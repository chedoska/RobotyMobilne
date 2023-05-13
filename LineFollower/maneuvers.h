#ifndef MANEUVERS_H
#define MANEUVERS_H

#include "motor_control.h"
#include "sensor_read.h"
#include "definitions.h"

#define TURN_DELAY_DURATION 350
#define GO_STRAIGHT_DELAY_DURATION 300
#define REVERSE_DELAY_DURATION 500

#define SPEED 180
#define SPEED_TURN 130
#define REVERSE_SPEED 130

#define BREAKING_TIME 200

#define OFFSET 20

void turn_left_90(){
  set_direction_both(FORW);
  set_speed_right(SPEED_TURN + OFFSET);
  set_speed_left(SPEED_TURN);
  delay(200);
  
  set_speed_right(SPEED_TURN + OFFSET);
  set_speed_left(0);
  delay(TURN_DELAY_DURATION);
  wait_until_sensor_right_1();
  set_speed_right(0);
}

void turn_right_90(){
  set_direction_both(FORW);
  set_speed_right(SPEED_TURN + OFFSET);
  set_speed_left(SPEED_TURN);
  delay(200);
  
  set_speed_left(SPEED_TURN);
  set_speed_right(0);
  delay(TURN_DELAY_DURATION);
  wait_until_sensor_left_1();
  set_speed_left(0);
}

void go_straight(){
  set_direction_both(FORW);
  set_speed_left(SPEED_TURN);
  set_speed_right(SPEED_TURN + OFFSET);
  delay(GO_STRAIGHT_DELAY_DURATION);
  set_speed_left(0);
  set_speed_right(0);
}

void reverse(){
  set_direction_right(BACK);
  set_direction_left(FORW);
  set_speed_left(REVERSE_SPEED);
  set_speed_right(REVERSE_SPEED + OFFSET);
  delay(REVERSE_DELAY_DURATION);
  wait_until_sensor_left_2();
  set_direction_both(FORW);
  set_speed_left(0);
  set_speed_right(REVERSE_SPEED + OFFSET);
  wait_until_sensor_right_1();
  set_speed_left(0);
  set_speed_right(0);
}

void stop_at_node(){
    set_speed_right(0);
    set_speed_left(0);
    set_direction_right(BACK);
    set_direction_left(BACK);
    delay(300);
    set_speed_right(REVERSE_SPEED + OFFSET + 10);
    set_speed_left(REVERSE_SPEED);
    while(!node_detected());
    delay(100);
    set_direction_right(FORW);
    set_direction_left(FORW);
    set_speed_right(0);
    set_speed_left(0);
}

#endif
