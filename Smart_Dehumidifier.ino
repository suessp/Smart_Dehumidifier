

#define LED 2 //Define blinking LED pin
#define POT A0

#define DIG1 D0
#define DIG2 D1
#define A D2
#define B D3
#define C D4
#define D D5
#define E D6
#define F D7
#define G D8
#define BUTTON GPIO 1
int potValue = 0;

volatile bool setFlag = false;

int segPins[] = {A, B, C, D, E, F, G};
byte seg_Array[10][7] = {   //A B C D E F G
                            { 0,0,0,0,0,0,1 },    // 0
                            { 1,0,0,1,1,1,1 },    // 1
                            { 0,0,1,0,0,1,0 },    // 2
                            { 0,0,0,0,1,1,0 },    // 3
                            { 1,0,0,1,1,0,0 },    // 4
                            { 0,1,0,0,1,0,0 },    // 5
                            { 0,1,0,0,0,0,0 },    // 6
                            { 0,0,0,1,1,1,1 },    // 7
                            { 0,0,0,0,0,0,0 },    // 8
                            { 0,0,0,1,1,0,0 }};   // 9
void setup() {

pinMode(LED, OUTPUT); // Initialize the LED pin as an output
  pinMode(POT, INPUT);
  pinMode(DIG1, OUTPUT);
  pinMode(DIG2, OUTPUT);
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(BUTTON), interrupt, RISING);  
}

int startTime = 0;
int endTime;
int i = 0, j = 0;
int d1 =0, d2 = 0;
// the loop function runs over and over again forever
void loop() {

  for(int i=0; i<32; i++){
    potValue += analogRead(POT);
  }
  potValue = potValue/32;
  potValue = map(analogRead(POT), 1, 1023, 0, 99);
  d1 = potValue%10;
  d2 = potValue/10;
  refreshDisplay(d2, d1);

   endTime = millis();                  // increments the counter approximately once a second
   if ((endTime - startTime) >= 1000)
   {
      potValue = potValue/32;
      potValue = map(analogRead(POT), 1, 1023, 0, 99);
      d1 = potValue%10;
      d2 = potValue/10;
   }
  delay(10);
  refreshDisplay(d2, d1);
}


//implements digit multiplexing
void refreshDisplay(int digit1,int digit0){
  digitalWrite(DIG1, LOW);                   //display digit 1
  digitalWrite(DIG2, HIGH);
  setSevenSeg(digit0);
  delay(5);
  digitalWrite(DIG1, HIGH);
  digitalWrite(DIG2, LOW);
  if(digit1==0){
    digitalWrite(DIG2, HIGH);
  }
  setSevenSeg(digit1);
  delay(5);
}

//sets segment pins
void setSevenSeg(int number){
  int pin = 2; //begining pin starting at A.
  for(int i=0; i<7; i++){
    digitalWrite(pin, seg_Array[number][i]);
    pin++;
  }
}

void interrupt(){
  if(setFlag){
    setFlag = false;
  }
  else{
    setFlag = true;
  }
}