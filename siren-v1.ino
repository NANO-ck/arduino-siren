#define buzz 10 //change to any output pin (not analog inputs) 

int i;
void setup() {
  pinMode(buzz, OUTPUT);
}

void loop() {
  tone(buzz, 435, 600);
  delay(600);
  noTone(buzz);
  tone(buzz, 580, 600); // 580 Hz is the frequency for police sirens
  delay(600);
  noTone(buzz);
}
