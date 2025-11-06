int prevstate = 0;
int state;
int val = 0;
const int N = 1;
int d = 0;

int encodeInt(int a, int b) {
  return 2*a + b;
}

int delta(int a, int b) {
  if((a == 1 && b == 0) || (a == 2 && b == 3)) {
    return 1;
  } else if((a == 2 && b == 0) || (a == 1 && b == 3)) {
    return -1;
  } else {
    return 0;
  }
}

void setup() {
  // put your setup code here, to run once:
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(15, OUTPUT);
  pinMode(16, INPUT);
  pinMode(30, INPUT);
  pinMode(31, INPUT);
  Serial.begin(9600);

//  int s = millis();
//  for(int i=0; i<10000; i++) {
//    for(int d=0; d<16; d++) {  // all 16ch mux reads = ~425us
//      digitalWrite(12, (d >> 3) % 2);
//      digitalWrite(13, (d >> 2) % 2);
//      digitalWrite(14, (d >> 1) % 2);
//      digitalWrite(15, d % 2);
//      state = digitalRead(16);
//    }
//  }
//  Serial.println(millis() - s);
//
//  s = millis();
//  for(int i=0; i<10; i++) Serial.println("abcdefgh");
//  Serial.println(millis() - s);
}

void loop() {
//  prevstate = encodeInt(digitalRead(30), digitalRead(31));
  for(int i=0; i<N; i++) {
    state = encodeInt(digitalRead(30), digitalRead(31));
    if(state != prevstate) {
      d = delta(prevstate, state);
      if(d != 0) {
        val += d;
        Serial.print(millis() / 1000); 
        Serial.print("s: "); 
        Serial.println(val); 
      }
      prevstate = state;
    }

  }
  
  delay(3);
    delayMicroseconds(500);
}
