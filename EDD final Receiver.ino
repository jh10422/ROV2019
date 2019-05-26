#include "Servo.h"
#include <Wire.h>


char joy[15];

 const int MaxPower = 2000;
 const int MaxRevPower = 1000;
 
 const int MaxFourPower = 2000;
 const int MaxFourRevPower = 1000;

 
String  FBSpeed;
String VertSpeed; 
String TurnSpeed; 

int  fbSpeed;
int turnSpeed;
int vertSpeed; 


String Joystick;
String message; 

Servo OutputM1;
Servo OutputM2;
Servo OutputM3;
Servo OutputM4;


int speed01;
int speed02;
int speed07;
int speed08;
int speed09;
int speed10;



boolean fourMotors;
boolean twoMotors;
boolean vertMotors;



void setup() {
  Serial1.begin(9600);
  fourMotors = false;
  twoMotors = false;
  pinMode(LED_BUILTIN, OUTPUT);

  OutputM1.attach(3);
  OutputM2.attach(4);
  OutputM3.attach(5);
  OutputM3.attach(12);

  
  OutputM1.writeMicroseconds(1500);
  OutputM2.writeMicroseconds(1500);
  OutputM3.writeMicroseconds(1500);
  OutputM4.writeMicroseconds(1500);


    speed01 = 1500;
    speed02 = 1500;
    speed07 = 1500;
    speed08 = 1500;
    speed09 = 1500;
    speed10 = 1500;
    delay(500);
}

void loop() {
  
  
  
  Serial1.readBytes(joy,15);
  Joystick = String(joy);
  
  FBSpeed = Joystick.substring((Joystick.indexOf("R") + 1), Joystick.indexOf("F"));
  TurnSpeed = Joystick.substring((Joystick.indexOf("F") + 1), Joystick.indexOf("U"));
  VertSpeed = Joystick.substring((Joystick.indexOf("U") + 1), Joystick.length());


  fbSpeed = FBSpeed.toInt();
  turnSpeed = TurnSpeed.toInt();
  vertSpeed = VertSpeed.toInt();




   if((fbSpeed == 0) and (turnSpeed == 0)){
      fourMotors = false;
      twoMotors = false;
      OutputM1.writeMicroseconds(1500);
      OutputM2.writeMicroseconds(1500);

    }
    
   if( vertSpeed == 0){
      vertMotors = false;
      fourMotors = false;
      OutputM3.writeMicroseconds(1500);
      OutputM4.writeMicroseconds(1500);
   }
    
    
    
   if (vertSpeed > 0) { //Up  
       vertMotors = true;
       if(fourMotors == false){
          speed08= map( vertSpeed, 0, 25, 1500, MaxPower);
          OutputM3.writeMicroseconds(speed08);
          OutputM4.writeMicroseconds(speed08);
       }

       if(fourMotors == true){
          speed08= map( vertSpeed, 0, 25, 1500, MaxFourPower);
          OutputM3.writeMicroseconds(speed08);
          OutputM4.writeMicroseconds(speed08);
       }

  }
        
  if (vertSpeed < 0) { //Down     
     vertMotors = true;
     vertSpeed = abs(vertSpeed);
     if( fourMotors == false){
        speed10 = map(vertSpeed,0, 25, 1500, MaxRevPower);
        OutputM3.writeMicroseconds(speed10);
        OutputM4.writeMicroseconds(speed10);
     }

     if( fourMotors == true){
        speed10 = map(vertSpeed,0, 25, 1500, MaxFourRevPower);
        OutputM3.writeMicroseconds(speed10);
        OutputM4.writeMicroseconds(speed10);
     }
   
  }

   if (fbSpeed > 0) { //Forwards
          twoMotors = true;
     if( fourMotors == false){
          speed07 = map(fbSpeed, 0, 25, 1500, MaxPower);
          OutputM1.writeMicroseconds(speed07);
          OutputM2.writeMicroseconds(speed07);
     }
     if( fourMotors == true){
          speed07 = map(fbSpeed, 0, 25, 1500, MaxFourPower);
          OutputM1.writeMicroseconds(speed07);
          OutputM2.writeMicroseconds(speed07);
     }

  }
  
  if (fbSpeed < 0) { //Backwards
          twoMotors = true;
          if(fourMotors == false){
            fbSpeed = abs(fbSpeed);
            speed09 = map(fbSpeed, 0, 25, 1500, MaxRevPower);
            OutputM1.writeMicroseconds(speed09);
            OutputM2.writeMicroseconds(speed09);
          }
            if(fourMotors == false){
              fbSpeed = abs(fbSpeed);
              speed09 = map(fbSpeed, 0, 25, 1500, MaxFourRevPower);
              OutputM1.writeMicroseconds(speed09);
              OutputM2.writeMicroseconds(speed09);
          }

  }
  
 if (turnSpeed > 0) { // Turn Right 
        twoMotors = true;
        if( fourMotors == false){
          speed01 = map(turnSpeed, 0, 25, 1500, MaxPower);
          speed02 = map(turnSpeed, 0, 25, 1500, MaxRevPower);
          OutputM1.writeMicroseconds(speed01);
          OutputM2.writeMicroseconds(speed02);
        }

        if( fourMotors == true){
          speed01 = map(turnSpeed, 0, 25, 1500, MaxFourPower);
          speed02 = map(turnSpeed, 0, 25, 1500, MaxFourRevPower);
          OutputM1.writeMicroseconds(speed01);
          OutputM2.writeMicroseconds(speed02);
        }

    
  }

   if (turnSpeed < 0) { // Turn Left
    twoMotors = true;
    turnSpeed = abs(turnSpeed);
    if( fourMotors == false){
        speed01 = map(turnSpeed, 0, 25, 1500, MaxPower);
        speed02 = map(turnSpeed, 0, 25, 1500, MaxRevPower);
        OutputM1.writeMicroseconds(speed02);
        OutputM2.writeMicroseconds(speed01);
    }

    if( fourMotors == true){
        speed01 = map(turnSpeed, 0, 25, 1500, MaxFourPower);
        speed02 = map(turnSpeed, 0, 25, 1500, MaxFourRevPower);
        OutputM1.writeMicroseconds(speed02);
        OutputM2.writeMicroseconds(speed01);
    }

   
  }
  
  if(twoMotors == true and vertMotors == true){
    fourMotors = true;
    
  }
  if ((fbSpeed == 0) and (turnSpeed == 0) and (vertSpeed  == 0)  ){
    twoMotors = false;
    vertMotors = false;
    OutputM1.writeMicroseconds(1500);
    OutputM2.writeMicroseconds(1500);
    OutputM3.writeMicroseconds(1500);
    OutputM4.writeMicroseconds(1500);
    speed01 = 1500;
    speed02 = 1500;
    speed07 = 1500;
    speed08 = 1500;
    speed09 = 1500;
    speed10 = 1500;
   }  
 
if (twoMotors == true or vertMotors == true){
    digitalWrite(LED_BUILTIN, HIGH);
  }
  
if (twoMotors == false and vertMotors == false){
    digitalWrite(LED_BUILTIN, LOW);
  }
  
  } 
