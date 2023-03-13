#define MS millis()
#define do1K s = millis(); for(uint32_t i=0; i<1000; i++)
#define do10K s = millis(); for(uint32_t i=0; i<10000; i++)
#define do100K s = millis(); for(uint32_t i=0; i<100000; i++)
#define do1M s = millis(); for(uint32_t i=0; i<1000000; i++)

unsigned long s;
int val;

void printTime(int start, const char* title);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(15, OUTPUT);
  pinMode(21, INPUT);
  pinMode(22, INPUT);
  pinMode(23, INPUT);
  pinMode(24, INPUT);
  pinMode(25, INPUT);

  Serial.println("---");

  do100K {
    digitalWrite(11, HIGH);
    digitalWrite(12, HIGH);
    digitalWrite(13, HIGH);
    digitalWrite(14, HIGH);
    digitalWrite(15, HIGH);
  } printTime(s, "500K x All high outputs: ");

  do100K {
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
    digitalWrite(14, LOW);
    digitalWrite(15, LOW);
  } printTime(s, "500K x All low outputs: ");

  do100K {
    digitalWrite(11, i&1);
    digitalWrite(12, i&1);
    digitalWrite(13, i&1);
    digitalWrite(14, i&1);
    digitalWrite(15, i&1);
  } printTime(s, "500K x Alternating: ");

  do100K {
    digitalRead(21);
    digitalRead(22);
    digitalRead(23);
    digitalRead(24);
    digitalRead(25);
  } printTime(s, "500K x Digital reads: ");

  do10K {
    analogRead(A3);
    analogRead(A4);
    analogRead(A5);
    analogRead(A6);
    analogRead(A7);
  } printTime(s, "50K x Analog reads: ");
}

void loop() {
  // put your main code here, to run repeatedly:

}

void printTime(unsigned long start, const char* title) {
  unsigned long t = millis() - start;
  Serial.print(title);
  Serial.println(t);
}

/* OUTCOMES:
- 1M alternating output pin states: 5972ms
- 1M same output pin states: 4841ms
*/
