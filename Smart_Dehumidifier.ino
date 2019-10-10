#include <ESP8266WiFi.h>

#define LED 2 //Define blinking LED pin
#define POT A0

#define DIG1 0
#define DIG2 1
#define A 2
#define B 3
#define C 4
#define D 5
#define E 6
#define F 7
#define G 8

const char* ssid0 = "FlavorTown";
const char* ssid1 = "FlavorTown_EXT";
const char* password = "tim3tooilup";

int target_Humidity = 0; 

//Manual override variables. Used to manually override target humidity using a potentiometer and seven seg display
int potValue = 0;
int segPins[] = {A, B, C, D, E, F, G};
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
int dig0 = 0;
int dig1 = 0;
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


  int connectedCount = 1;
  
  WiFi.begin(ssid0, password);
  
  while (WiFi.status() != WL_CONNECTED){ //wait for connection to FlavorTown
    DitgitalWrite(LED, HIGH);
    delay(1000);
    DigitalWrite(LED, LOW);
    if(connectedCount >= 20){             //if 20 seconds have passed, attempt to connect to FlavorTown_EXT
      connectedCount = 1;
      WiFi.begin(ssid1, password);
    }
    connectedCount++;
  }
  DigitalWrite(LED, HIGH);

}
// the loop function runs over and over again forever
void loop() {
  while(buttonFlag){
    readPot();
    refreshDisplay(dig1, dig0);
  }

   
  //digitalWrite(LED, LOW); // Turn the LED on (Note that LOW is the voltage level)
  //delay(1000); // Wait for a second
  //digitalWrite(LED, HIGH); // Turn the LED off by making the voltage HIGH
  //delay(1000); // Wait for two seconds
  potValue = map(analogRead(POT), 1, 1023, 0, 9);
  refreshDisplay(potValue);
  //SevenSegPrint(DIG1, 9);
}


//implements digit multiplexing
void refreshDisplay(int num){
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  int digit0 = num%10;
  int digit1 = num/10;
  digitalWrite(DIG1, LOW);                   //display digit 1
  digitalWrite(DIG2, HIGH);
  setSevenSeg(digit0);
  delay(5);
  digitalWrite(DIG1, HIGH);                  //display digit 2
  digitalWrite(DIG2, LOW);
  setSevenSeg(digit1);
  delay(5);
  pinMode(A, INPUT);
  pinMode(B, INPUT);
}

//sets segment pins
void setSevenSeg(int number){
  int pin = 2; //begining pin starting at A.
  for(int i=0; i<7; i++){
    digitalWrite(pin, num_array[number][i]);
    pin++;
  }
}

void readPot(){
  float alpha = 0.6;
  int potValue = analogRead(POT);
  potValue = (alpha*potValue) + ((1-alpha)*potValue);
  map(potValue, 1, 1023, 0, 99);
  targetHumidity = potValue;
  dig0 = potValue%10;
  dig1 = potValue/10;
}