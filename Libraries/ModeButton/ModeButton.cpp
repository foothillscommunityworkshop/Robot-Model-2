#include <ModeButton.h>
#include <Arduino.h>


int _buttonPin;
volatile int buttonCounter = 0;
volatile long StartTime;
volatile long diffTime;

int MAXTIME = 10000;

void ModeButtonSetup(int buttonPin)
{
    _buttonPin = buttonPin;
    
    pinMode(buttonPin, INPUT_PULLUP);
    
    if(buttonPin == 8)
    {
        //Setting up D8 for the button
        PCMSK0 |= bit (PCINT0); // want pin D8
        PCIFR |= bit (PCIF0); // clear any outstanding interrupts
        PCICR |= bit (PCIE0); // enable pin change interrupts for D8 to D13
    }
    
}


ISR (PCINT0_vect) {
    // handle pin change interrupt for D8 to D13 here
    if(digitalRead(_buttonPin) == HIGH)
    {
       long currentTime = millis();
       
            diffTime = currentTime - StartTime;
            if(diffTime < MAXTIME)
            {
                if(buttonCounter < 4)
                {
                    buttonCounter++;
                }
                
            }
            else
            {
                StartTime = currentTime;
                buttonCounter = 0;
            }
     
      /*
        digitalWrite(13,HIGH);
        delay(200);
        digitalWrite(13,LOW);
       */
    }
    
    
    
} // end of PCINT0_vect

int GetButtonCount()
{
    return buttonCounter;
}
