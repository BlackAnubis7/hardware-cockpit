#define _S0 40
#define _S1 41
#define _S2 42
#define _S3 43
#define _SIG 53
#define _EN 52 

// int dat[] = {0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0};
int S0 = 0, S1 = 0, S2 = 0, S3 = 0, SIG = 0, EN = 0;

void flush() {
  digitalWrite(_S0, S0);
  digitalWrite(_S1, S1);
  digitalWrite(_S2, S2);
  digitalWrite(_S3, S3);
  digitalWrite(_EN, EN);
//  delay(1);
}

void setup() {
  Serial.begin(115200);
  pinMode(_S0, OUTPUT);
  pinMode(_S1, OUTPUT);
  pinMode(_S2, OUTPUT);
  pinMode(_S3, OUTPUT);
  pinMode(_SIG, INPUT);
  pinMode(_EN, OUTPUT); 
  pinMode(29, OUTPUT); 
  pinMode(31, OUTPUT); 

  flush();

  S3 = 1; S2 = 1; SIG = 1;  // 1100 = 12
  flush();
  delay(1000);
  S2 = 0; S1 = 1; SIG = 1;  // 1010 = 10
  EN = 0;
  flush();
}

void setBin(int i) {
  S0 = (i>>0) % 2;
  S1 = (i>>1) % 2;
  S2 = (i>>2) % 2;
  S3 = (i>>3) % 2;
}

void loop() {
  for(int i=0; i<16; i++) {
    setBin(i);
    flush();
    SIG = digitalRead(_SIG);
    if(i==4) digitalWrite(31, SIG);
    else if(i==10) digitalWrite(29, SIG);
  }
}