#ifndef INPUTS_H
#define INPUTS_H

#include "Arduino.h"
#include "definitions.h"

#define OPTION_1  30
#define OPTION_2  210
#define OPTION_3  351
#define OPTION_4  565
#define OPTION_5  723
#define OPTION_6  883

#define OPTION_TOLERANCE 50

#define PRESS_TIME 15 // PRESS_TIME x 10 ms
#define RELEASE_TIME 20

uint8_t option_node_id_array[] = {0,1,2,5,8,7};

int16_t option_array_values[] = {OPTION_1, OPTION_2, OPTION_3, OPTION_4, OPTION_5, OPTION_6};

uint8_t current_selected_option(){
  int16_t analog_value = analogRead(OPTION_POT);
  for(int i = 0; i < 6; i++){
    if(abs(analog_value - option_array_values[i]) < OPTION_TOLERANCE){
      return i + 1;
    }
  }
}

uint8_t start_is_pressed(){
  return digitalRead(BUTTON_START_PIN) ? 0 : 1;
}

uint8_t stop_is_pressed(){
  return digitalRead(BUTTON_STOP_PIN) ? 0 : 1;
}

uint8_t start_is_pressed_for_time(){
  uint16_t press_time = PRESS_TIME;
  while(press_time-- > 0){
    if(!start_is_pressed()) return 0;
    delay(10);
  }
  return 1;
}

uint8_t stop_is_pressed_for_time(){
  uint16_t press_time = PRESS_TIME;
  while(press_time-- > 0){
    if(!stop_is_pressed()) return 0;
    delay(10);
  }
  return 1;
}

void wait_until_start_released(){
  uint16_t release_time = RELEASE_TIME;
  while(release_time-- > 0){
    if(start_is_pressed())
      release_time = RELEASE_TIME;
    delay(10);
  }
}

void wait_until_stop_released(){
  uint16_t release_time = RELEASE_TIME;
  while(release_time-- > 0){
    if(stop_is_pressed())
      release_time = RELEASE_TIME;
    delay(10);
  }
}

uint8_t pot_option_to_node_id(uint8_t option){
  return option_node_id_array[option-1];
}

#endif
