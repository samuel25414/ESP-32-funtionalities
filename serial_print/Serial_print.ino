void setup() {
  Serial.begin(115200);
  delay(2000);
  Serial.println("Hola desde ESP32");
}

void loop() {
  Serial.println("Loop OK");
  delay(1000);
}