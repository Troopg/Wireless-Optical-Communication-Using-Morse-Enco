int ledPin = 8;

void dot() {

  digitalWrite(ledPin, HIGH);

  delay(500);

  digitalWrite(ledPin, LOW);

  delay(1500);
}

void letterGap() {

  delay(10000);
}

void sendH() {

  // H = ....
  dot();
  dot();
  dot();
  dot();

  letterGap();
}

void sendI() {

  // I = ..
  dot();
  dot();

  letterGap();
}

void setup() {

  pinMode(ledPin, OUTPUT);

  delay(10000);
}

void loop() {

  sendH();

  sendI();

  delay(15000);
}
