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
  pinMode(48, INPUT);
  pinMode(52, INPUT);
  Serial.begin(9600);
}

void loop() {
//  prevstate = encodeInt(digitalRead(52), digitalRead(48));
  for(int i=0; i<N; i++) {
    state = encodeInt(digitalRead(52), digitalRead(48));
    if(state != prevstate) {
      d = delta(prevstate, state);
      if(d != 0) {
        val += d;
        Serial.println(val); 
      }
      prevstate = state;
    }

  }
  
//  delay(2);
    delayMicroseconds(500);
}
