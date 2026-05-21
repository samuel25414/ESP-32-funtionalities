#include <Wire.h>

#define EEPROM_ADDR 0x50   // 24LC256 address when A0, A1, A2 are connected to GND

void writeByte(unsigned int memoryAddress, byte data) {
  Wire.beginTransmission(EEPROM_ADDR);

  // 24LC256 needs 2 address bytes: high byte first, low byte second
  Wire.write((memoryAddress >> 8) & 0xFF);
  Wire.write(memoryAddress & 0xFF);

  Wire.write(data);
  Wire.endTransmission();

  delay(5); // wait for internal EEPROM write cycle
}

byte readByte(unsigned int memoryAddress) {
  Wire.beginTransmission(EEPROM_ADDR);

  // Set memory address to read from
  Wire.write((memoryAddress >> 8) & 0xFF);
  Wire.write(memoryAddress & 0xFF);
  Wire.endTransmission();

  Wire.requestFrom(EEPROM_ADDR, 1);

  if (Wire.available()) {
    return Wire.read();
  }

  return 0xFF; // error/default value
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  Wire.begin(21, 22); // SDA = GPIO21, SCL = GPIO22

  Serial.println("24LC256 EEPROM demo");

  unsigned int address = 0x0000;
  byte valueToWrite = 123;

  Serial.print("Writing value: ");
  Serial.println(valueToWrite);

  writeByte(address, valueToWrite);

  byte valueRead = readByte(address);

  Serial.print("Value read from EEPROM: ");
  Serial.println(valueRead);

  if (valueRead == valueToWrite) {
    Serial.println("Success: write and read worked!");
  } else {
    Serial.println("Error: value read is different.");
  }
}

void loop() {
}