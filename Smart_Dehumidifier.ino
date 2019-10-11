#include <ESP8266WiFi.h>


static const uint8_t D0   = 16;
static const uint8_t D1   = 5;
static const uint8_t D2   = 4;
static const uint8_t D3   = 0;
static const uint8_t D4   = 2;
static const uint8_t D5   = 14;
static const uint8_t D6   = 12;
static const uint8_t D7   = 13;
static const uint8_t D8   = 15;
static const uint8_t D9   = 3;
static const uint8_t D10  = 1;



#define ANALOG A0     //analog read pin

#define DIG1 D0       //output pin for seven seg digit 1 enable
#define DIG2 D1       //output pin for seven seg digit 2 enable
#define RELAY D2      //output pin for relay signal
#define A_MUX D3      //output pin for both segment A and Mux select sig
#define B_BUTTON D4   //output pin for segment B and input pin for interrupt button
#define C D5          //output pin for segment C
#define D D6          //output pin for segment D
#define E D7          //output pin for segment E
#define F D8          //output pin for segment F
#define WLEVEL D9     //interrupt pin for water level circuit
#define G D10         //output pin for segment G


volatile bool setFlag = false;



const char* ssid0 = "FlavorTown";
const char* ssid1 = "FlavorTown_EXT";
const char* password = "tim3tooilup";

int targetHumidity = 0; 

//Manual override variables. Used to manually override target humidity using a potentiometer and seven seg display
int potValue = 0;
int segPins[] = {A_MUX, B_BUTTON, C, D, E, F, G};
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
int dig0 = 0;
int dig1 = 0;
void setup() {

  pinMode(ANALOG, INPUT);
  pinMode(DIG1, OUTPUT);
  pinMode(DIG2, OUTPUT);
  pinMode(A_MUX, OUTPUT);
  pinMode(B_BUTTON, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(B_BUTTON), interrupt, RISING);  
  attachInterrupt(digitalPinToInterrupt(WLEVEL), reservoirFull, RISING);

  int connectedCount = 1;
  int startTime = 0;
  int endTime;
  int i=0, j=0;

  WiFi.begin(ssid0, password);
  
  while (WiFi.status() != WL_CONNECTED){ //wait for connection to FlavorTown
    refreshDisplay(dig1, dig0); 
    endTime = millis();                  // increments the counter approximately once a second
    if ((endTime - startTime) >= 1000){
      connectedCount++;
      startTime = endTime;
    }
    if(connectedCount >= 20){             //if 20 seconds have passed, attempt to connect to FlavorTown_EXT
      connectedCount = 1;
      WiFi.begin(ssid1, password);
    }
    dig0 = connectedCount%10;
    dig1 = connectedCount/10;
  }
  

}

int startTime = 0;
int endTime;
int i = 0, j = 0;
int d1 =0, d2 = 0;
// the loop function runs over and over again forever
void loop() {
  while(setFlag){
    readPot();
    refreshDisplay(dig1, dig0);
  }


}


//implements digit multiplexing
void refreshDisplay(int digit1,int digit0){
  pinMode(B_BUTTON, OUTPUT);
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
  pinMode(B_BUTTON, INPUT);
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

void readPot(){
  digitalWrite(A_MUX, HIGH);
  float alpha = 0.6;
  int potValue = analogRead(ANALOG);
  potValue = (alpha*potValue) + ((1-alpha)*potValue);
  map(potValue, 1, 1023, 0, 99);
  targetHumidity = potValue;
  dig0 = potValue%10;
  dig1 = potValue/10;
  digitalWrite(A_MUX, LOW);
}

void reservoirFull(){

}