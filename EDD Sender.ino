#include "Servo.h"

#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>

#include <SPI.h>
#include <RF24.h>

RF24 radio(7, 8); 
const byte address[6] = "00001";


const int InputA0 = A0; // Forward and Backward
const int InputA1 = A1; // Turning
const int InputA2 = A2; // Up and down



int PotA2 = 0; 
int PotA5;



int outputValueZ = 0; 
int ZDirection = 0; 

int SpeedY = 0;
int SpeedX = 0;
int SpeedZ = 0; 
int SpeedT = 0;
int SpeedP = 0;

int XSpeed;
int YSpeed;
int RawX;
int RawY;
int MappedX;
int MappedY;
int XDirect;
int YDirect;

String strSpeedXY;
String strSpeedZ; 
String rotMeasure; 

String JoystickData;
char joy[15];



String data;

typedef struct
 {
     String data;
 }  Joystick;


Joystick firstJoy; // Lateral Movement And Forward/Reverse
Joystick secondJoy; // Vertical Pitch and Rotional Right/Left

 
void setup() {

  Serial.begin(9600); // initialize Serial
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  delay(500);

}

void loop() {
  PotA2 = analogRead(InputA2); 
  outputValueZ = map(PotA2, 0, 1023, -25, 25); // map potentiometer Readings of Joystick 
  configure("First", InputA1, InputA0, "F");
  
  if (outputValueZ >= 3){ 
     ZDirection = 1; // Up
  }
  if (outputValueZ <= -3){
     ZDirection = -1; // Down
  }
  if ((outputValueZ < 3) and (outputValueZ> -3) ) {
     ZDirection = 0; // Not moving Vertically
  }
  SpeedZ = ZDirection * abs(outputValueZ); // Vertical Speed 
  strSpeedZ = String(SpeedZ); // Convert SpeedZ into a string
  
  JoystickData = "R"+firstJoy.data+ "U"  +strSpeedZ;
  JoystickData.toCharArray(joy,15);
  radio.write(joy,15);
  //delay(50);
}


void configure(String Type , const int Xpin, const int Ypin, String Between){
  XSpeed;
  YSpeed;
  RawX = analogRead(Xpin);
  RawY = analogRead(Ypin);
  MappedX = map(RawX, 0, 1023, -25, 25);
  MappedY = map(RawY, 0, 1023, -25, 25);
  XDirect;
  YDirect;
  String XY;
  if((MappedX <= -3 and MappedX >= -24) and (MappedY <= abs(MappedX) and MappedY >= 0) and (MappedY != 25)){
    XDirect = -1;
    YDirect = 0;
}
  
if( (MappedX <= -3 and MappedX >= -24) and (MappedY >= MappedX and MappedY < 0) and (MappedY != 25)){
    XDirect = -1;
    YDirect = 0;

}
  if((MappedX == -25) and (abs(MappedY) <= 24)){
    XDirect = -1;
    YDirect = 0;

}
       
  if( (MappedX >= 3 and MappedX <= 24) and (abs(MappedY)<= MappedX and MappedY < 0) and (MappedY != 25)){
    XDirect = 1;
    YDirect = 0;

  }
  
  if( (MappedX >= 3 and MappedX <= 24) and (MappedY <= MappedX and MappedY >= 0) and (MappedY != 25)){
    XDirect = 1;
    YDirect = 0;
  }
  if((MappedX == 25) and ( abs(MappedY) <= 24)){
    XDirect = 1;
    YDirect = 0;

  }

  if(((MappedX >= -24 and MappedX <= -3) or (MappedX >= 3 and MappedX <= 24)) and (MappedY > 0 and MappedY > abs(MappedX))){
    YDirect = 1;
    XDirect = 0;
  }
  if(( abs(MappedX) == 25 ) and (MappedY == 25)){
    YDirect = 1;
    XDirect = 0;
  }
  if((MappedX >= -3 and MappedX <= 3) and (MappedY >= 3)) {
    YDirect = 1;
    XDirect = 0;

  }
  
     if( ((MappedX >= -24 and MappedX <= -3) or (MappedX >= 3 and MappedX <= 24)) and ( MappedY < 0 and MappedY < (-1 * abs(MappedX)))){
     YDirect = -1;
     XDirect = 0;
  }
  
  if( ( abs(MappedX) == 25 ) and (MappedY == -25 )){
     YDirect = -1;
     XDirect = 0;
  }
  
  if((MappedX >= -3 and MappedX <= 3) and MappedY <= -3){
    YDirect = -1;
    XDirect = 0;
  }    

  if( (MappedX <= 3 and MappedX >= -3) and (MappedY <= 2 and MappedY >= -2) ){
    YDirect = 0;
    XDirect = 0;
}
  
  YSpeed = YDirect * abs(MappedY);
  XSpeed = XDirect * abs(MappedX);
  XY = String(XSpeed) + Between + String(YSpeed);
  if(Type == "First"){
    firstJoy.data = XY;
  }
  if(Type =="Second"){
    secondJoy.data = XY;
  }
} 
