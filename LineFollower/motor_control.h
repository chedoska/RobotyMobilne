#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include "definitions.h"
#include "Arduino.h"

enum Direction {FORW, BACK};

void set_speed_right(uint8_t m_speed){
  analogWrite(EN_P_PIN, m_speed);
}

void set_speed_left(uint8_t m_speed){
  analogWrite(EN_L_PIN, m_speed);
}

void set_direction_right(Direction m_direction){
  if(m_direction == FORW){
    digitalWrite(IN1_P_PIN, HIGH);
    digitalWrite(IN2_P_PIN, LOW);
  }
  else{
    digitalWrite(IN1_P_PIN, LOW);
    digitalWrite(IN2_P_PIN, HIGH);
  }
}

void set_direction_left(Direction m_direction){
  if(m_direction == FORW){
    digitalWrite(IN3_L_PIN, HIGH);
    digitalWrite(IN4_L_PIN, LOW);
  }
  else{
    digitalWrite(IN3_L_PIN, LOW);
    digitalWrite(IN4_L_PIN, HIGH);
  }
}

void set_direction_both(Direction m_direction){
  set_direction_left(m_direction);
  set_direction_right(m_direction);
}

void break_right(uint8_t break_time, Direction m_direction_after){
  digitalWrite(IN1_P_PIN, LOW);
  digitalWrite(IN2_P_PIN, LOW);
  delay(break_time);
  set_direction_right(m_direction_after);
}

void break_left(uint8_t break_time, Direction m_direction_after){
  digitalWrite(IN3_L_PIN, LOW);
  digitalWrite(IN4_L_PIN, LOW);
  delay(break_time);
  set_direction_left(m_direction_after);
}

void break_both(uint8_t break_time, Direction m_direction_after_left, Direction m_direction_after_right){
  digitalWrite(IN1_P_PIN, LOW);
  digitalWrite(IN2_P_PIN, LOW);
  digitalWrite(IN3_L_PIN, LOW);
  digitalWrite(IN4_L_PIN, LOW);
  delay(break_time);
  set_direction_right(m_direction_after_right);
  set_direction_left(m_direction_after_left);
}

#endif
