#define _DAI 25
#define _DCK 27
#define _LAT 29
#define _EN 30 

// int dat[] = {0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0};
int EN = 0, DAI = 0, DCK = 0, LAT = 0;

void flush() {
  digitalWrite(_DAI, DAI);
  digitalWrite(_DCK, DCK);
  digitalWrite(_LAT, LAT);
  digitalWrite(_EN, EN);
//  Serial.print(DAI);
//  Serial.print(DCK);
//  Serial.print(LAT);
//  Serial.print(EN);
//  Serial.println();
//  delay(1);
}

void setup() {
  Serial.begin(115200);
  pinMode(46, INPUT);
  pinMode(_DAI, OUTPUT);
  pinMode(_DCK, OUTPUT);
  pinMode(_LAT, OUTPUT);
  pinMode(_EN, OUTPUT);

  flush();
}

void loop() {
  for(int i=0; i<64; i++) {
    if(i%2 == 0) DCK = 1;
    else {
      DCK = 0;
    //   DAI = dat[(i+1) / 2];
      DAI = (((i+1)/2) % 2 == 0 && digitalRead(46));
    }
    flush();
  }
  LAT = 1;
  flush();
  delay(1);
  LAT = 0;
  flush();
}