#include "PiezoBuzzer.h"
#include "Arduino.h"


//Pin to use for the buzzer
int _pinId;
int _buzzerLength = 100;

//Set the pin to use for the buzzer on the construtor
PiezoBuzzer::PiezoBuzzer(int pinId)
{
  //Set the pinId to output.
  pinMode(pinId, OUTPUT);
  _pinId = pinId;
}

void PiezoBuzzer::SetBuzzerLength(int buzzerLength)
{
    _buzzerLength = buzzerLength;
}

//Create a short burst of buzzer sound.
void PiezoBuzzer::Beep(int amount)
{
  //Check to make sure that the pinId is valid to use.
  if(_pinId > 0)
  {
      for (int i = 0; i < amount; i++)
      {
          digitalWrite(_pinId, HIGH);
          delay(_buzzerLength);
          digitalWrite(_pinId, LOW);
      }
     
  }
}


