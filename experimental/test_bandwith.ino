char buf[16];
int rb = 0;

void setup() {
  Serial.begin(115200);
}

void loop() {
  rb = Serial.readBytesUntil('\0', buf, 16);
  if(rb == 16) {
    if(buf[0] == '1' && buf[15] == '1') buf[15] == '9';
    else if(buf[0] == '2' && buf[15] == '2') buf[15] == '8';
    else buf[15] == '0';
  }
  else buf[15] == '0';
  Serial.write(&(buf[8]), 8);
  delay(1);
}