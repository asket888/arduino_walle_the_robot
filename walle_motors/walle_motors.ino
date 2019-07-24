// motor one
int enA = 10;
int in1 = 9;
int in2 = 8;

// motor two
int enB = 5;
int in3 = 7;
int in4 = 6;

// ultrasonic
#define PIN_ECHO 11
#define PIN_TRIG 12
long duration, distance;

void setup() {
  Serial.begin (9600);

  // ultrasonic
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}

void move_forward(int speed, int duration)
{
  analogWrite(enA, speed);
  analogWrite(enB, speed);
  
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH); 
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  delay(duration);
}

void move_back(int speed, int duration)
{
  analogWrite(enA, speed);
  analogWrite(enB, speed);
  
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW); 
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  delay(duration);
}

void stop(int duration)
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW); 
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);

  delay(duration);
}

void turn_right(int speed, int duration)
{
  analogWrite(enA, speed);
  analogWrite(enB, speed);
  
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH); 
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  delay(duration);
}

void turn_left(int speed, int duration)
{
  analogWrite(enA, speed);
  analogWrite(enB, speed);
  
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW); 
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  delay(duration);
}

long echo_space()
{
  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(5);
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);

  duration = pulseIn(PIN_ECHO, HIGH);
  distance = (duration / 2) / 29.1;

  if (distance <= 30){
    turn_right(170, 500);
    stop(100);
  }

  move_forward(170, 500);
  stop(100);

  Serial.print("Distance to an object: ");
  Serial.print(distance);
  Serial.println(" cm.");

  delay(250);
}  


void loop() {
  echo_space();
  stop(1000);
}
