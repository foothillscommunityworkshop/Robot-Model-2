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
    
    //Setup the Button Pin
    pinMode(buttonPin, INPUT_PULLUP);
    
    if(buttonPin == 8)
    {
        //We are setting the Pin and Inerrupt for the button on pin D8.
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
        //Get the CurrentTime
       long currentTime = millis();
        
            //Get the difference
            diffTime = currentTime - StartTime;
        
            //See if the diffence is less than the max amount of time if so we are still in
            // within the time limit of the last pin press. If so then increase the count up to a max
            // of 4 If the time limit is exceeded, then reset the button to 0.
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

    }
    
    
    
} // end of PCINT0_vect

int GetButtonCount()
{
    return buttonCounter;
}
