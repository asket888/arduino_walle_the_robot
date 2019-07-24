
// bluzzer
int PIN_BLUZ = 13;
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
  pinMode(PIN_BLUZ, OUTPUT);
}

void sound_hello() 
{
  tone(PIN_BLUZ, d, 250);
  delay(300);
  tone(PIN_BLUZ, aS, 250);
  delay(300);
  tone(PIN_BLUZ, fSH, 500);
  delay(600);
  noTone(PIN_BLUZ);
}

void sound_upset()
{
  tone(PIN_BLUZ, eH, 250);
  delay(300);
  tone(PIN_BLUZ, c, 500);
  delay(600);
  noTone(PIN_BLUZ);
}

void loop() {

}
