// ultrasonic
#define PIN_TRIG A0
#define PIN_ECHO A1
long duration, cm;

// bluzzer
int PIN_BLUZ = 11;
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
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);

  // bluzzer
  pinMode(PIN_BLUZ, OUTPUT);
}

void sound_upset()
{
  tone(PIN_BLUZ, eH, 250);
  delay(250);
  tone(PIN_BLUZ, c, 500);
  delay(500);
  noTone(PIN_BLUZ);
}

void echo()
{
  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(5);
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);

  duration = pulseIn(PIN_ECHO, HIGH);
  cm = (duration / 2) / 29.1;

  Serial.print("Расстояние до объекта: ");
  Serial.print(cm);
  Serial.println(" см.");

  delay(100);
}  

void loop() {
  echo();
}
