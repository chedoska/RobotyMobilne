#ifndef SENSOR_READ_H
#define SENSOR_READ_H

#include "definitions.h"
#include "Arduino.h"
#include <stdint.h>

#define PREFIX ! // Wykrywanie czarnego na białym tle

#define NODE_DETECT_FILTER_STR 5
#define WAIT_UNTIL_FILTER_STR 5

uint8_t sensor_left_2(){
  return PREFIX digitalRead(SENS_L_2);
}

uint8_t sensor_left_1(){
  return PREFIX digitalRead(SENS_L_1);
}

uint8_t sensor_right_1(){
  return PREFIX digitalRead(SENS_P_1);
}

uint8_t sensor_right_2(){
  return PREFIX digitalRead(SENS_P_2);
}

//void read_sensor_filter{


uint8_t node_detected(){
  static int readCount = 0;
  if(sensor_left_2()  &&
     sensor_left_1()  &&
     sensor_right_1() &&
     sensor_right_2()){
    readCount++;
     }
  else{
    readCount = 0;
  }
  if(readCount > NODE_DETECT_FILTER_STR)
    return true;
  else
    return false;
}

void wait_until_sensor_left_2(){
  uint8_t counter = 0;
  while(counter < WAIT_UNTIL_FILTER_STR){
    if(sensor_left_2()) counter++;
    else counter = 0;
  }
}

void wait_until_sensor_left_1(){
  uint8_t counter = 0;
  while(counter < WAIT_UNTIL_FILTER_STR){
    if(sensor_left_1()) counter++;
    else counter = 0;
  }
}

void wait_until_sensor_right_1(){
  uint8_t counter = 0;
  while(counter < WAIT_UNTIL_FILTER_STR){
    if(sensor_right_1()) counter++;
    else counter = 0;
  }
}

void wait_until_sensor_right_2(){
  uint8_t counter = 0;
  while(counter < WAIT_UNTIL_FILTER_STR){
    if(sensor_right_2()) counter++;
    else counter = 0;
  }
}

#endif
