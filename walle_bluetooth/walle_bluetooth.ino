#include <Servo.h>
Servo head_servo;
char command; 

void setup() {
  Serial.begin(9600);
  head_servo.attach(4);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  if(Serial.available() > 0) { 
    command = Serial.read(); 
    switch(command) {
    case 'F':  
      led_on();
      break;
    case 'B':  
      led_off();
      break;
    case 'L':  
      head_move(90);
      break;
    case 'R':
      head_move(180);
      break;
    }
  }
}

void led_on() {
  digitalWrite(LED_BUILTIN, HIGH);
}

void led_off() {
  digitalWrite(LED_BUILTIN, LOW);
}


void head_move(int angle)
{
  head_servo.write(angle);
}
