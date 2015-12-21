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

//Pin Senor 
const int EchoPin = 2;
const int TrigPin = 4;

//Buzzer 
const int BuzzerPin = 7;

//Mode button
const int ModeButton = 8;

//Radio 
const int radioPinCe = 9;
const int radioPinCs = 10;

//Servo's
const int RServoPin = 5;
const int LServoPin = 6;

//Create Buzzer object
PiezoBuzzer piezoBuzzer(BuzzerPin);

void setup() {
  // put your setup code here, to run once:

 //Onboard LED
  pinMode(13, OUTPUT);

  //We are setting the radios to listen on the Channel.
 RadioSetup(radioPinCe, radioPinCs);

 //Setup the Servo's to be used
 FcwServoSetup(RServoPin, LServoPin);

 //Setup the Pin sensor for use. 
 PingSensorSetup(TrigPin,EchoPin);
   
  Serial.begin (115200);  
}

void loop() {
  // put your main code here, to run repeatedly:

 //Test to make sure the we are not to close to something 
if (CurrentDuration() < TooClose)
  {
    //Turn Random 
      TurnRandom();
      piezoBuzzer.Beep(1);
      Serial.println("turn");
      Serial.print("Dur:");
      Serial.println(CurrentDuration());
  }
  else
  {
    //Run straight
     Run(1);
     Serial.println("Run");
     Serial.print("Dur:");
     Serial.println(CurrentDuration());  
  }

 // Get the current slave command. If its A then beep
  if(GetSlaveCommand() == "A")
  {
      piezoBuzzer.Beep(2);
  }
        delay(500);

  /*      
//Create and send 3 different letters as slave commands.       
SendCommand("A");
delay(500);
SendCommand("B");
delay(500);
SendCommand("C");
*/
        //faking a work load 
     //   delay(500);
}





