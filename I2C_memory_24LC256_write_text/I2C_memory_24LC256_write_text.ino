#include <Wire.h>

#define EEPROM_ADDR 0x50

void writeByte(unsigned int memoryAddress, byte data) {
  Wire.beginTransmission(EEPROM_ADDR);
  Wire.write((memoryAddress >> 8) & 0xFF);
  Wire.write(memoryAddress & 0xFF);
  Wire.write(data);
  Wire.endTransmission();

  delay(5);
}

byte readByte(unsigned int memoryAddress) {
  Wire.beginTransmission(EEPROM_ADDR);
  Wire.write((memoryAddress >> 8) & 0xFF);
  Wire.write(memoryAddress & 0xFF);
  Wire.endTransmission();

  Wire.requestFrom(EEPROM_ADDR, 1);

  if (Wire.available()) {
    return Wire.read();
  }

  return 0xFF;
}

void writeText(unsigned int startAddress, const char* text) {
  int i = 0;

  while (text[i] != '\0') {
    writeByte(startAddress + i, text[i]);
    i++;
  }

  // Save string terminator
  writeByte(startAddress + i, '\0');
}

void readText(unsigned int startAddress, char* buffer, int maxLength) {
  for (int i = 0; i < maxLength - 1; i++) {
    char c = readByte(startAddress + i);

    buffer[i] = c;

    if (c == '\0') {
      return;
    }
  }

  buffer[maxLength - 1] = '\0';
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  Wire.begin(21, 22);

  Serial.println("Writing text to 24LC256...");

  unsigned int startAddress = 0x0010;

  writeText(startAddress, "Hello ESP32 EEPROM");

  char message[50];

  readText(startAddress, message, sizeof(message));

  Serial.print("Text read: ");
  Serial.println(message);
}

void loop() {
}