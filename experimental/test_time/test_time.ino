#define MS millis()
#define do1K s = millis(); for(uint32_t i=0; i<1000; i++)
#define do10K s = millis(); for(uint32_t i=0; i<10000; i++)
#define do100K s = millis(); for(uint32_t i=0; i<100000; i++)
#define do1M s = millis(); for(uint32_t i=0; i<1000000; i++)

int s;
int val;

void printTime(int start, const char* title);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(21, INPUT);
  pinMode(22, INPUT);
  pinMode(23, INPUT);
  pinMode(24, INPUT);

  do1M {
    digitalWrite(11, HIGH);
  } printTime(s, "states: ");

//  Serial.println(sizeof(int64_t));
}

void loop() {
  // put your main code here, to run repeatedly:

}

void printTime(int start, const char* title) {
  int t = millis() - start;
  Serial.print(title);
  Serial.println(t);
}

/* OUTCOMES:
- 1M alternating output pin states: 5972ms
- 1M same output pin states: 4841ms
*/
