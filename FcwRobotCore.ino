/*
 * PiezoBuzzer:
 *    Beep(int amount);
 *    
 * PingSensor:   
 *    PingSensorSetup(TrigPin,EchoPin);
 *    CurrentDuration();
 *    
 * ModeButton:   
 *    ModeButtonSetup(ModeButton);
 *    GetButtonCount();
 *    
 * FcwRadio:   
 *     RadioSetup(radioPinCe, radioPinCs);
 *     SendCommand(Char*);
 *     GetSlaveCommand();
 *     
 */

#include "PiezoBuzzer.h"
#include "PingSensor.h"
#include "ModeButton.h"
#include "FcwRadio.h"
#include "FcwServo.h"


const int TooClose = 300;

const int EchoPin = 2;
const int TrigPin = 4;
const int BuzzerPin = 7;
const int ModeButton = 8;

const int radioPinCe = 9;
const int radioPinCs = 10;

const int RServoPin = 5;
const int LServoPin = 6;

PiezoBuzzer piezoBuzzer(BuzzerPin);

void setup() {
  // put your setup code here, to run once:

 //Onboard LED
  pinMode(13, OUTPUT);

  //We are setting the radios to listen on the Channel.
 RadioSetup(radioPinCe, radioPinCs);

 FcwServoSetup(RServoPin, LServoPin);

 PingSensorSetup(TrigPin,EchoPin);
   
  Serial.begin (115200);  
}

void loop() {
  // put your main code here, to run repeatedly:
if (CurrentDuration() < TooClose)
        {
          TurnRandom();
         piezoBuzzer.Beep(1);
          Serial.println("turn");
          Serial.print("Dur:");
          Serial.println(CurrentDuration());
        }
        else
        {
          //Run straight
          Serial.println("Run");
          Serial.print("Dur:");
          Serial.println(CurrentDuration());
          Run(1);
        }

       Serial.print("SlaveCommand:");
       Serial.println(GetSlaveCommand());

       if(GetSlaveCommand() == "A")
       {
         piezoBuzzer.Beep(2);
  
        delay(500);

  /*      
SendCommand("A");
delay(500);
SendCommand("B");
delay(500);
SendCommand("C");
*/
        //faking a work load 
     //   delay(500);
}





