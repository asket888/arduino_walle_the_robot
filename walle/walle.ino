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
long sonic_pulse_in;
long sonic_distance;

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

// bluetooth
char bluetooth_command;

void setup() {
  // serial
  Serial.begin(9600);
  
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

// dc motors controll
void dc_move_forward(int speed_A, int speed_B, int duration) {
  analogWrite(enA, speed_A);
  analogWrite(enB, speed_B);
  
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH); 
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  delay(duration);
}

void dc_move_back(int speed_A, int speed_B, int duration) {
  analogWrite(enA, speed_A);
  analogWrite(enB, speed_B);
  
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW); 
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  delay(duration);
}

void dc_turn_right(int speed, int duration) {
  analogWrite(enA, speed);
  analogWrite(enB, speed);
  
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH); 
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  delay(duration);
}

void dc_turn_left(int speed, int duration) {
  analogWrite(enA, speed);
  analogWrite(enB, speed);
  
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW); 
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  delay(duration);
}

void dc_stop() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW); 
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

// servo motor controll
void servo_move_head(int angle) {
  servo_head.write(angle);
}

void servo_move_left_hand(int angle) {
  servo_left_hand.write(angle);    
}

void servo_move_right_hand(int angle) {
  servo_right_hand.write(angle);
}

// robot base actions
void down_head() {
  servo_move_head(105);
}

void up_head() {
  servo_move_head(135);
}

void down_hands() {
  servo_move_left_hand(100);
  servo_move_right_hand(90);
}

void up_hands() {
  servo_move_left_hand(160);
  servo_move_right_hand(30);
}

void shake_head(int num, int delay_time) {
  for (int i = 0; i < num; i++) {
    up_head();
    delay(delay_time);
    down_head();
    delay(delay_time);
  }
}

void shake_hands(int num, int delay_time) {
  for (int i = 0; i < num; i++) {
    servo_move_left_hand(160);
    servo_move_right_hand(30);
    delay(delay_time);
    servo_move_left_hand(100);
    servo_move_right_hand(90);
    delay(delay_time);
  }
}

void wave_hands(int num, int delay_time) {
  for (int i = 0; i < num; i++) {
    servo_move_left_hand(100);
    servo_move_right_hand(30);
    delay(delay_time);
    servo_move_left_hand(160);
    servo_move_right_hand(90);
    delay(delay_time);
  }
}

void sound_upset() {
  tone(BLUZ_PIN, eH, 250);
  delay(250);
  tone(BLUZ_PIN, c, 500);
  delay(500);
  noTone(BLUZ_PIN);
}

long echo_space() {
  digitalWrite(SONIC_TRIG_PIN, LOW);
  delayMicroseconds(5);
  digitalWrite(SONIC_TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(SONIC_TRIG_PIN, LOW);

  sonic_pulse_in = pulseIn(SONIC_ECHO_PIN, HIGH);
  sonic_distance = (sonic_pulse_in / 2) / 29.1;

  return sonic_distance;
} 

// robot behavior
void check_for_obstacle() {
  sonic_distance = echo_space();
  if (sonic_distance < 20) {
    dc_stop();
    shake_hands(2, 100);
    sound_upset();
    dc_move_back(120, 120, 300);
      while(Serial.available()) {
        Serial.read();
    }
    dc_stop();
  }
}

void check_for_controll_input() {
  if(Serial.available() > 0) { 
    bluetooth_command = Serial.read(); 
    dc_stop();
    switch(bluetooth_command) {
    case 'F':  // forward
      dc_move_forward(150, 150, 5);
      break;
    case 'B':  // backward
      dc_move_back(150, 150, 5);
      break;
    case 'G':  // left & forward
      dc_move_forward(0, 200, 5);
      break;
    case 'I':  // right & forward
      dc_move_forward(200, 0, 5);
      break;
    case 'H':  // left & backward
      dc_move_back(0, 200, 5);
      break;
    case 'J':  // right & backward
      dc_move_back(200, 0, 5);
      break;    
    case 'L':  // turn left on place
      dc_turn_left(120, 5);
      break;
    case 'R': // turn right on place
      dc_turn_right(120, 5);
      break;
    case 'V': // make a beep
      sound_upset();
      break;
    case 'v': // make a beep
      sound_upset();
      break;  
    case 'W': // hands up
      up_hands();
      break;
    case 'w': // hands down
      down_hands();
      break;
    case 'X': // make a shake hands move
      shake_hands(3, 200);
      break;
    case 'x': // make a wave hands move
      wave_hands(3, 200);
      break;    
    case 'U': // make a shake haed move
      shake_head(1, 300);
      break;
    case 'u': // make a shake haed move
      shake_head(1, 300);
      break;  
    }
  }
}

void loop() {
  check_for_obstacle();
  check_for_controll_input();
}
