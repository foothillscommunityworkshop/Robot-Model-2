#include "PiezoBuzzer.h"
#include "Arduino.h"


//Pin to use for the buzzer
int _BuzzerPinId;;
int _buzzerLength = 100;

//Set the pin to use for the buzzer on the construtor
void PiezoBuzzerSetup(int pinId)
{
  //Set the pinId to output.
  pinMode(pinId, OUTPUT);
  _BuzzerPinId = pinId;
}
void SetBuzzerLength(int buzzerLength)
{
    _buzzerLength = buzzerLength;
}

//Create a short burst of buzzer sound.
void Beep(int amount)
{
  //Check to make sure that the pinId is valid to use.
  if(_BuzzerPinId > 0)
  {
      for (int i = 0; i < amount; i++)
      {
          digitalWrite(_BuzzerPinId, HIGH);
          delay(_buzzerLength);
          digitalWrite(_BuzzerPinId, LOW);
      }
     
  }
}


