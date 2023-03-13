void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  unsigned long t = millis();
  for(int i=0; i<1000; i++) {
    // send 100 bytes
    Serial.println("_________1_________2_________3_________4_________5_________6_________7_________8_________9_________0");
  }
  Serial.println(millis() - t);
}

void loop() {
  // put your main code here, to run repeatedly:
  
}
