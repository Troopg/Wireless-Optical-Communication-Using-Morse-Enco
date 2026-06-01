#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

int threshold = 550;

bool lightDetected = false;

unsigned long startTime = 0;

String morseCode = "";

String finalMessage = "";

unsigned long lastSignalTime = 0;

void setup() {

  Serial.begin(9600);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  display.clearDisplay();
}

char decodeMorse(String code) {

  if(code == "....") return 'H';

  if(code == "..") return 'I';

  return '?';
}

void showMessage() {

  display.clearDisplay();

  display.setTextSize(4);

  display.setTextColor(WHITE);

  display.setCursor(10,20);

  display.println(finalMessage);

  display.display();
}

void loop() {

  int val = analogRead(A0);

  // LIGHT START
  if(val > threshold && !lightDetected) {

    lightDetected = true;

    startTime = millis();
  }

  // LIGHT END
  if(val < threshold && lightDetected) {

    lightDetected = false;

    unsigned long duration = millis() - startTime;

    // DOT
    if(duration < 2000) {

      morseCode += ".";
    }

    lastSignalTime = millis();
  }

  // LETTER COMPLETE
  if(morseCode.length() > 0 &&
     millis() - lastSignalTime > 7000) {

    char letter = decodeMorse(morseCode);

    // ADD LETTER TO MESSAGE
    finalMessage += letter;

    Serial.println(finalMessage);

    showMessage();

    // CLEAR CURRENT LETTER ONLY
    morseCode = "";

    delay(2000);
  }
}
