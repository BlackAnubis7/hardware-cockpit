#define DAI 46
#define CLK 48
#define LOAD 52

const char* s1 = "0000110000000001";
const char* sS = "0000101111111010";
const char* sB = "1011100111111111";
const char* s2 = "0000000110111011";
const char* sD = "0001100100000001";
const char* s3 = "0000001111110111";
const char* s4 = "0000001000000000";

void flush(const char* s) {  // normal one-chip flush() needs more or less 1.2ns
  int b, d;
  digitalWrite(LOAD, LOW);
  for(int i=0; i<=32; i++) {
    if(i%2==0) {
      digitalWrite(CLK, HIGH);
    } else {
      d = s[i/2];
      b = (d == '1') ? HIGH : LOW;
      digitalWrite(DAI, b);
      digitalWrite(CLK, LOW);
    }
  }
  digitalWrite(DAI, LOW);
//  for(int i=1; i<=32; i++) {
//    if(i%2==0) {
//      digitalWrite(CLK, HIGH);
//    } else {
////      d = s[i/2];
////      b = (d == '1') ? HIGH : LOW;
////      digitalWrite(DAI, LOW);
//      digitalWrite(CLK, LOW);
//    }
//  }
  digitalWrite(CLK, LOW);
  digitalWrite(LOAD, HIGH);
  delay(1);
  digitalWrite(CLK, HIGH);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(DAI, OUTPUT);
  pinMode(CLK, OUTPUT);
  pinMode(LOAD, OUTPUT);
  digitalWrite(DAI, LOW);
  digitalWrite(CLK, LOW);
  digitalWrite(LOAD, HIGH);
  delay(1000);

  flush(s1);
  flush(sS);
  flush(sB);
//  flush(s2);
  flush(sD);
  Serial.begin(9600);
  int __s = millis();
  for(int i=0; i<10000; i++) {
    flush(s4);
  }
  Serial.println(millis() - __s);
  flush(s3);
}

void loop() {
  // put your main code here, to run repeatedly:
  
}
