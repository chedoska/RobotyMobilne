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

#define SPEED 210
#define TURN_SPEED 190

#define FILTER_STR 100
#define FILTER_STR_2 100

enum Maneuver{TURN_LEFT, TURN_RIGHT, STOP, GO_STRAIGHT, REVERSE};
Maneuver maneuverList[] = {GO_STRAIGHT, TURN_RIGHT, TURN_LEFT, REVERSE, TURN_RIGHT, TURN_LEFT, GO_STRAIGHT, STOP};
bool stoped = false;
static int filteredCounters[4] = {0,0,0,0};

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

  //----------------------------------------------

  digitalWrite(IN3_L_PIN, HIGH);
  digitalWrite(IN1_P_PIN, HIGH);
}

void readFiltered(){
  if(digitalRead(SENS_L_2) == 0) filteredCounters[0]++;
  else filteredCounters[0] = 0;
  if(digitalRead(SENS_L_1) == 0) filteredCounters[1]++;
  else filteredCounters[1] = 0;
  if(digitalRead(SENS_P_1) == 0) filteredCounters[2]++;
  else filteredCounters[2] = 0;
  if(digitalRead(SENS_P_2) == 0) filteredCounters[3]++;
  else filteredCounters[3] = 0;
}

void setMotorsForward(){
  digitalWrite(IN3_L_PIN, HIGH);
  digitalWrite(IN1_P_PIN, HIGH);
  digitalWrite(IN4_L_PIN, LOW);
  digitalWrite(IN2_P_PIN, LOW);
}

void setMotorsBackward(){
  digitalWrite(IN3_L_PIN, LOW);
  digitalWrite(IN1_P_PIN, LOW);
  digitalWrite(IN4_L_PIN, HIGH);
  digitalWrite(IN2_P_PIN, HIGH);
}
void goStraight(){
  setMotorsForward();
  analogWrite(EN_L_PIN, TURN_SPEED);
  analogWrite(EN_P_PIN, TURN_SPEED);
  delay(350);
  analogWrite(EN_L_PIN, 0);
  analogWrite(EN_P_PIN, 0);
}

void turnLeft_90(){
  setMotorsForward();
  analogWrite(EN_L_PIN, 0);
  analogWrite(EN_P_PIN, TURN_SPEED);
  delay(300);
  int val1 = 0;
  while(val1 < FILTER_STR_2){
    if(digitalRead(SENS_P_1) == 0) val1++;
    else val1 = 0;
  }
  analogWrite(EN_P_PIN, 0);
}

void turnRight_90(){
  setMotorsForward();
  analogWrite(EN_P_PIN, 0);
  analogWrite(EN_L_PIN, TURN_SPEED);
  delay(300);
  int val1 = 0;
  while(val1 < FILTER_STR_2){
    if(digitalRead(SENS_L_1) == 0) val1++;
    else val1 = 0;
  }
  analogWrite(EN_L_PIN, 0);
}

void stop_robot(){
  analogWrite(EN_P_PIN, 0);
  analogWrite(EN_L_PIN, 0);
  stoped = true;
}

void reverse(){
  setMotorsBackward();
  analogWrite(EN_P_PIN, TURN_SPEED);
  analogWrite(EN_L_PIN, 0);
  delay(1700);
  setMotorsForward();
  analogWrite(EN_P_PIN, 0);
  analogWrite(EN_L_PIN, TURN_SPEED);
  int val1 = 0;
  while(val1 < FILTER_STR_2){
    if(digitalRead(SENS_L_1) == 0) val1++;
    else val1 = 0;
  }
  analogWrite(EN_L_PIN, 0);
  analogWrite(EN_P_PIN, TURN_SPEED);
  val1 = 0;
  while(val1 < FILTER_STR_2){
    if(digitalRead(SENS_P_1) == 0) val1++;
    else val1 = 0;
  }
  analogWrite(EN_P_PIN, 0);
}

void executeManeuver(Maneuver maneuver){
  switch(maneuver){
    case Maneuver::TURN_LEFT:
      turnLeft_90();
      break;
    case Maneuver::TURN_RIGHT:
      turnRight_90();
      break;
    case Maneuver::GO_STRAIGHT:
      goStraight();
      break;
    case Maneuver::STOP:
      stop_robot();
      break;
    case Maneuver::REVERSE:
      reverse();
      break;
  }
}

int currentManuverIndex = 0;

void loop() {  
  readFiltered();
  if(stoped) return;
  
  if(digitalRead(SENS_L_1) == 0){
    analogWrite(EN_L_PIN, 0);
    analogWrite(EN_P_PIN, SPEED);
  }
  else if(digitalRead(SENS_P_1) == 0){
    analogWrite(EN_L_PIN, SPEED);
    analogWrite(EN_P_PIN, 0);
  }
  else{
    analogWrite(EN_P_PIN, SPEED);
    analogWrite(EN_L_PIN, SPEED);
  }

  /*if(digitalRead(SENS_L_1) == 0 && digitalRead(SENS_L_2) == 0 &&
     digitalRead(SENS_P_1) == 0 && digitalRead(SENS_P_2) == 0){
     executeManeuver(maneuverList[currentManuverIndex++]);*/

  if(filteredCounters[0] > FILTER_STR &&
     filteredCounters[1] > FILTER_STR &&
     filteredCounters[2] > FILTER_STR &&
     filteredCounters[3] > FILTER_STR){
      executeManeuver(maneuverList[currentManuverIndex++]);
  }
}
