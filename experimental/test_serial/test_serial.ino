unsigned char buf[256];
char succ[5];
int len, received;
unsigned long long s;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.setTimeout(1000);
}

void loop() {
  for(int i=0; i<256; i++) buf[i] = 0;
  len = -1; received = -1;
  // put your main code here, to run repeatedly:
  if(Serial.available() > 0) {
    s = micros();
    len = Serial.read();
    if(len >= 0) received = Serial.readBytes(buf, len);

    succ[0] = len & 0xFF;
    succ[1] = received & 0xFF;
    succ[2] = len >= 2 ? buf[len - 2] : 0xFF;
    succ[3] = len >= 1 ? buf[len - 1] : 0xFF;
    s = (micros() - s) / 10;
    succ[4] = s < 256 ? (unsigned char) (s&0xFF) : 0xFF;
    Serial.write(succ, 5);
  }
  delay(1);
}
