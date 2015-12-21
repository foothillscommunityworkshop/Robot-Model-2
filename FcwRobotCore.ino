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


const int EchoPin = 2;
const int TrigPin = 4;
const int BuzzerPin = 7;
const int ModeButton = 8;

const int radioPinCe = 9;
const int radioPinCs = 10;

PiezoBuzzer piezoBuzzer(BuzzerPin);

void setup() {
  // put your setup code here, to run once:

  //Onboard LED
  pinMode(13, OUTPUT);

  //We are setting the radios to listen on the Channel.
 RadioSetup(radioPinCe, radioPinCs);

  
  Serial.begin (115200);   
}

void loop() {
  // put your main code here, to run repeatedly:

  for(int i; i< 5; i++)
  {
    SendCommand("B");
    delay(500);
  }
  
  for(int i; i< 5; i++)
  {
    SendCommand("C");
    delay(500);
  }
  SendCommand("A");
  
  delay(500);
}





