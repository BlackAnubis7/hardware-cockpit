#define DAI 46
#define CLK 48
#define LOAD 52

const char* s1 = "0000110000000001";  // unshutdown
// const char* sS = "0000101111111010";  // display only digits 0, 1 and 2
const char* sS = "0000101111111111";  // display all digits
const char* sO = "0000101000000010";  // set brightness (change rightmost 4 bits to change brightness)
const char* sB = "1011100111111111";  // use Code B for all digits
const char* s2 = "0000000110111011";  // display E on digit 0 (with a dot)
const char* sD = "0001100100000001";  // do not use Code B for digits 7-1 anymore
const char* s3 = "0000001111110111";  // display all but bottom segment on digit 2 (including the dot)
const char* s4 = "0000001000001100";  // make digit 1 display two segments

// normal one-chip flush() needs more or less 1.2ms
//     However, 1ms of this is sleeping - other things can be done
void flush(const char* s) {  
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
  flush(sO);
  flush(sS);
  flush(sB);
  flush(s2);
  flush(sD);
  Serial.begin(9600);
//  int __s = millis();
//  for(int i=0; i<10000; i++) {
//    flush(s4);
//  }
//  Serial.println(millis() - __s);
  flush(s3);
  flush(s4);
}

void loop() {
  // put your main code here, to run repeatedly:
  
}
