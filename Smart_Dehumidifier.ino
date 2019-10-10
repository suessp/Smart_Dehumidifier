/*
ESP8266 Blink
Blink the blue LED on the ESP8266 module
*/

#define LED 2 //Define blinking LED pin
#define Potentiometer A0

#define DIG1 0
#define DIG2 1
#define A 2
#define B 3
#define C 4
#define D 5
#define E 6
#define F 7
#define G 8

int potBits = 0;

byte Seg_Array[10][7] = {   //A B C D E F G
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
  pinMode(Potentiometer, INPUT);
  pinMode(DIG1, OUTPUT);
  pinMode(DIG2, OUTPUT);
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT);
  
}
// the loop function runs over and over again forever
void loop() {
  //digitalWrite(LED, LOW); // Turn the LED on (Note that LOW is the voltage level)
  //delay(1000); // Wait for a second
  //digitalWrite(LED, HIGH); // Turn the LED off by making the voltage HIGH
  //delay(1000); // Wait for two seconds
  potBits = analogRead(Potentiometer);
  SevenSegPrint(DIG1, map(potBits, 1, 1024, 0, 10));
  //SevenSegPrint(DIG1, 9);
}

void refreshDisplay(int digit1, int digit0){

}

void SevenSegPrint(int digit, int number){
  digitalWrite(digit, LOW);
  int pin = 2;

  int num_array[10][7] = {  //A B C D E F G
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

  for(int i=0; i<7; i++){
    digitalWrite(pin, num_array[number][i]);
    pin++;
  }
}