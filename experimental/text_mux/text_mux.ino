void setup() {
  // put your setup code here, to run once:
  pinMode(46, OUTPUT);
  pinMode(44, OUTPUT);
  pinMode(42, OUTPUT);
  pinMode(40, OUTPUT);
  pinMode(38, INPUT);

  digitalWrite(46, LOW);
  digitalWrite(44, HIGH);
  digitalWrite(42, LOW);
  digitalWrite(40, HIGH);

  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(digitalRead(38));
  delay(1024);
}
