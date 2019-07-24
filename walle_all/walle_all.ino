// servo
#include <Servo.h>
Servo servo_head;
Servo servo_left_hand;
Servo servo_right_hand;
int SERVO_HEAD_PIN = 4;
int SERVO_L_HAND_PIN = 2;
int SERVO_R_HAND_PIN = 3;

// motor one
int enA = 10;
int in1 = 9;
int in2 = 8;

// motor two
int enB = 5;
int in3 = 7;
int in4 = 6;

// ultrasonic
#define SONIC_TRIG_PIN A0
#define SONIC_ECHO_PIN A1
long sonic_pulse_in, sonic_distance;

// bluzzer
int BLUZ_PIN = 11;
const int c = 261;
const int d = 294;
const int e = 329;
const int f = 349;
const int g = 391;
const int gS = 415;
const int a = 440;
const int aS = 455;
const int b = 466;
const int cH = 523;
const int cSH = 554;
const int dH = 587;
const int dSH = 622;
const int eH = 659;
const int fH = 698;
const int fSH = 740;
const int gH = 784;
const int gSH = 830;
const int aH = 880;

void setup() {
  // serial
  Serial.begin (9600);
  
  // ultrasonic
  pinMode(SONIC_TRIG_PIN, OUTPUT);
  pinMode(SONIC_ECHO_PIN, INPUT);

  // motor A
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  // motor B
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  // bluzzer
  pinMode(BLUZ_PIN, OUTPUT);

  // servo
  servo_head.attach(SERVO_HEAD_PIN);
  servo_left_hand.attach(SERVO_L_HAND_PIN);
  servo_right_hand.attach(SERVO_R_HAND_PIN);
}

void move_forward(int speed, int duration){
  analogWrite(enA, speed);
  analogWrite(enB, speed);
  
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH); 
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  delay(duration);
}

void move_back(int speed, int duration){
  analogWrite(enA, speed);
  analogWrite(enB, speed);
  
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW); 
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  delay(duration);
}

void stop(int duration){
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW); 
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);

  delay(duration);
}

void turn_right(int speed, int duration){
  analogWrite(enA, speed);
  analogWrite(enB, speed);
  
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH); 
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  delay(duration);
}

void turn_left(int speed, int duration){
  analogWrite(enA, speed);
  analogWrite(enB, speed);
  
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW); 
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  delay(duration);
}

void move_head(int angle){
  servo_head.attach(4);
  servo_head.write(angle);
}

void move_left_hand(int angle){
  servo_left_hand.write(angle);    
}

void move_right_hand(int angle){
  servo_right_hand.write(angle);
}

void straight_servos(){
  move_head(105);
  move_left_hand(120);
  move_right_hand(180);
}

void shake_head(){
  move_head(135);
  delay(300);
  move_head(105);
  delay(300);
}

void shake_hands(){
  move_left_hand(120);
  move_right_hand(180);
  delay(200);
  move_left_hand(180);
  move_right_hand(120);
  delay(200);
  straight_servos();
}

void sound_upset(){
  tone(BLUZ_PIN, eH, 250);
  delay(250);
  tone(BLUZ_PIN, c, 500);
  delay(500);
  noTone(BLUZ_PIN);
}

long echo_space(){
  digitalWrite(SONIC_TRIG_PIN, LOW);
  delayMicroseconds(5);
  digitalWrite(SONIC_TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(SONIC_TRIG_PIN, LOW);

  sonic_pulse_in = pulseIn(SONIC_ECHO_PIN, HIGH);
  sonic_distance = (sonic_pulse_in / 2) / 29.1;

  Serial.print("Расстояние до объекта: ");
  Serial.print(sonic_distance);
  Serial.println(" см.");

  return sonic_distance;
}  

void run_robot(){
  straight_servos();
  sonic_distance = echo_space();
  if (sonic_distance < 30){
    stop(200);
    sound_upset();
    shake_head();
    shake_hands();
    shake_hands();
    move_back(170, 200);
    turn_right(150, 300);
    stop(200);
  }
  else {
    move_forward(170, 50);
  }
}

void loop() {
  run_robot();
}
