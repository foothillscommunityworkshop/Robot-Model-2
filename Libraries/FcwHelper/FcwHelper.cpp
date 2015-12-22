#include "FcwHelper.h"
#include "Arduino.h"

#include "PingSensor.h"

//The distance from object before we change direction
const int TooClose = 300;


void FreeRangeMode()
{
    if (CurrentDuration() < TooClose)
    {
        //Turn Random
        //   TurnRandom();
        //    piezoBuzzer.Beep(1);
        Serial.println("turn");
        Serial.print("Dur:");
        Serial.println(CurrentDuration());
    }
    else
    {
        //Run straight
        //   Run(1);
        Serial.println("Run");
        Serial.print("Dur:");
        Serial.println(CurrentDuration());
    }
}

void MasterMode()
{
    
}


void DanceMode()
{
    //We need to have a timer between commands.
    //If we dont get a new one after XX amount of time
    //We revert back to freeRange
    Serial.println("Backward");
    //Run(2);
}