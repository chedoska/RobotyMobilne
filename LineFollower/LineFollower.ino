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

bool stoped = false;

void loop() {
  if(stoped){
    delay(300);
    return;
  }
  
  if(digitalRead(SENS_L_1) == 0){
    analogWrite(EN_L_PIN, 0);
    analogWrite(EN_P_PIN, 130);
  }
  else if(digitalRead(SENS_P_1) == 0){
    analogWrite(EN_L_PIN, 130);
    analogWrite(EN_P_PIN, 0);
  }
  else{
    analogWrite(EN_P_PIN, 130);
    analogWrite(EN_L_PIN, 130);
  }

  if(digitalRead(SENS_P_2) == 0 &&
     digitalRead(SENS_L_2) == 0){
        analogWrite(EN_P_PIN, 0);
        analogWrite(EN_L_PIN, 0);
        stoped = true;
     }
}
