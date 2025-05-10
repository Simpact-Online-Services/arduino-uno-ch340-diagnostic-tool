#include <Arduino.h>

#define LED_PIN 13  // Built-in LED on Arduino Uno

const int pattern[] = {200, 200, 600, 200, 200, 600}; // Blink-blink-long-blink-blink-long
const int patternLength = sizeof(pattern) / sizeof(pattern[0]);

unsigned long lastLoopTime = 0;
int loopCount = 0;

void printWithTimestamp(const String& msg) {
  unsigned long ms = millis();
  unsigned long s = ms / 1000;
  unsigned long ms_rem = ms % 1000;
  char buf[32];
  snprintf(buf, sizeof(buf), "[%5lu.%03lu] ", s, ms_rem);
  Serial.print(buf);
  Serial.println(msg);
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  delay(500);  // Helps with manual reset uploads
  Serial.begin(9600);
  printWithTimestamp("=== Setup complete ===");
}

void loop() {
  loopCount++;
  unsigned long now = millis();

  printWithTimestamp("=== Beginning loop iteration " + String(loopCount) + " ===");

  // Detect potential reset/stuck loop
  if (now - lastLoopTime < 100) {
    printWithTimestamp("WARNING: Loop running too fast - possible reset/stuck?");
  }
  lastLoopTime = now;

  for (int i = 0; i < patternLength; i++) {
    digitalWrite(LED_PIN, HIGH);
    printWithTimestamp("LED ON for " + String(pattern[i]) + " ms");
    delay(pattern[i]);

    digitalWrite(LED_PIN, LOW);
    printWithTimestamp("LED OFF for 150 ms");
    delay(150);
  }

  printWithTimestamp("Pattern complete. Loop restarting...");
  delay(1000);
}
