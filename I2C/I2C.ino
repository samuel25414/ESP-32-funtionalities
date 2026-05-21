#include <Wire.h>

void setup() {
  Serial.begin(115200);
  delay(1000);

  // ESP32 default I2C pins
  Wire.begin(21, 22); // SDA = GPIO21, SCL = GPIO22

  Serial.println("I2C Scanner starting...");
}

void loop() {
  byte error;
  byte address;
  int devices = 0;

  Serial.println("Scanning...");

  for (address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("I2C device found at address 0x");

      if (address < 16) {
        Serial.print("0");
      }

      Serial.println(address, HEX);
      devices++;
    }
  }

  if (devices == 0) {
    Serial.println("No I2C devices found.");
  } else {
    Serial.println("Scan finished.");
  }

  delay(3000);
}