// servo
#include <Servo.h>
Servo head_servo;
Servo left_hand_servo;
Servo right_hand_servo;

void setup() {
    left_hand_servo.attach(2);
   right_hand_servo.attach(3);
  // head_servo.attach(4);
}

void head_move(int angle)
{
  head_servo.write(angle);
}

void left_hand_move(int angle)
{
  left_hand_servo.write(angle);    
}

void right_hand_move(int angle)
{
  right_hand_servo.write(angle);
}

void shake_head()
{
  head_move(130);
  delay(300);
  head_move(90);
  delay(300);
}

void shake_hands()
{
  left_hand_move(120);
  right_hand_move(180);
  delay(200);
  left_hand_move(180);
  right_hand_move(120);
  delay(200);
}

void loop() {
  shake_hands();
}
