char buf[3];
int rb = 0;

void setup() {
  Serial.begin(115200);
}

void loop() {
  rb = Serial.readBytesUntil('\0', buf, 3);
  if(rb == 3) {
    buf[0] += 3;
    buf[1] += 3;
    buf[2] += 3;
    Serial.write(buf, 3);
  }
  delay(100);
}