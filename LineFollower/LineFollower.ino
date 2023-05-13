#include "maneuvers.h"
#include "path_planning.h"
#include "inputs.h"

uint8_t current_position_node_id = 0;
uint8_t current_node_enter_direction = 1;

Robot_State robot_state = STAND_BY;

Maneuver maneuverList[MAX_PATH_SIZE] = {GO_STRAIGHT, TURN_RIGHT, TURN_LEFT, REVERSE, TURN_RIGHT, TURN_LEFT, GO_STRAIGHT, STOP};
uint8_t programCounter = 0;

  Node_data mapa[] = {{0,{-1,-1,-1,1},{0,0,0,10}},
                      {1,{-1,0,2,4},{0,10,10,10}},
                      {2,{1,-1,-1,3},{10,0,0,10}},
                      {3,{4,2,-1,-1},{10,10,0,0}},
                      {4,{5,1,3,-1},{20,10,10,0}},
                      {5,{-1,-1,4,6},{0,0,20,30}},
                      {6,{-1,5,8,7},{0,30,25,30}},
                      {7,{-1,6,-1,-1},{0,30,0,0}},
                      {8,{6,-1,-1,-1},{25,0,0,0}}};

void setup() {
  pinMode(EN_L_PIN, OUTPUT);
  pinMode(IN4_L_PIN, OUTPUT);
  pinMode(IN3_L_PIN, OUTPUT);
  pinMode(IN2_P_PIN, OUTPUT);
  pinMode(IN1_P_PIN, OUTPUT);
  pinMode(EN_P_PIN, OUTPUT);

  digitalWrite(EN_L_PIN, HIGH);
  digitalWrite(IN4_L_PIN, LOW);
  digitalWrite(IN3_L_PIN, LOW);
  digitalWrite(IN2_P_PIN, LOW);
  digitalWrite(IN1_P_PIN, LOW);
  digitalWrite(EN_P_PIN, HIGH);

  pinMode(SENS_L_1, INPUT);
  pinMode(SENS_L_2, INPUT);
  pinMode(SENS_P_1, INPUT);
  pinMode(SENS_P_2, INPUT);

  pinMode(BUTTON_START_PIN, INPUT_PULLUP);
  pinMode(BUTTON_STOP_PIN, INPUT_PULLUP);

  pinMode(LED_BUILTIN, OUTPUT);

  set_direction_right(FORW);
  set_direction_left(FORW);
  set_speed_right(0);
  set_speed_left(0);

  /*uint8_t sizew = 0;
  uint8_t path[8];
  sizew = findNodePath(current_position_node_id, current_selected_option(), mapa, path);
  Maneuver lista[10];
  generateManeuverList(path, sizew, mapa, maneuverList, 3);
  maneuverList[sizew-1] = STOP;

  //delay(5000);*/
  //Serial.begin(9600);
}

void robot_stand_by_mode(){
  if(start_is_pressed_for_time()){
    wait_until_start_released();

    uint8_t picked_goal_node_id = pot_option_to_node_id(current_selected_option());
    uint8_t path_size;
    uint8_t path[MAX_PATH_SIZE];
    uint8_t end_direction_result;
    
    path_size = findNodePath(current_position_node_id, picked_goal_node_id, mapa, path);
    
    generateManeuverList(path, path_size, mapa, maneuverList, current_node_enter_direction, &end_direction_result);
    maneuverList[path_size - 1] = STOP;
    programCounter = 0;
    robot_state = EXECUTING_PATH;
    
    current_position_node_id = picked_goal_node_id;
    current_node_enter_direction = end_direction_result;
  }
  if(stop_is_pressed_for_time()){
    wait_until_stop_released();
    current_position_node_id =  pot_option_to_node_id(current_selected_option());
    current_node_enter_direction = 1;
  }
}

void robot_execute_path_mode(){    
  if(sensor_left_1()){
    set_speed_right(SPEED + OFFSET);
    set_speed_left(0);
  }
  else if(sensor_right_1()){
    set_speed_right(0);
    set_speed_left(SPEED);
  }
  else{
    set_speed_right(SPEED + OFFSET);
    set_speed_left(SPEED);
  }

  if(node_detected()){
    if(maneuverList[programCounter] == GO_STRAIGHT) go_straight();
    else if(maneuverList[programCounter] == TURN_RIGHT) turn_right_90();
    else if(maneuverList[programCounter] == TURN_LEFT) turn_left_90();
    else if(maneuverList[programCounter] == REVERSE) reverse();
    else {
      stop_at_node();
      robot_state = STAND_BY;
    }
    programCounter++;
  }  

  if(stop_is_pressed()){
    set_speed_right(0);
    set_speed_left(0);
    robot_state = STAND_BY;
  }
}

void loop() {
  if(robot_state == STAND_BY){
    digitalWrite(LED_BUILTIN, LOW);
    robot_stand_by_mode();
  }
  else{
    digitalWrite(LED_BUILTIN, HIGH);
    robot_execute_path_mode();
  }
}
