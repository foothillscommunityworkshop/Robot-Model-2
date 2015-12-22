#include "FcwHelper.h"
#include "Arduino.h"
#include "FcwServo.h"
#include "FcwRadio.h"

#include "PingSensor.h"

//The distance from object before we change direction
const int TooClose = 300;

typedef  struct {
    String DMove;
    int DNum;
} DanceMove;
const DanceMove DMoves[] = {{"1", 1000}, {"2",500}, {"3",1500}, {"4",1500}};


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
    for (int i; i < 4; i++)
    {
        DanceMove move1 = DMoves[i];
        
        String command = "B:";
        command.concat(move1.DMove);
        
        char commandToSend[command.length() + 1];
        command.toCharArray(commandToSend, command.length() + 1);
        
        //Send Command to the Slave bots
        SendCommand(commandToSend);
        
        //Process the Command ourself
        ProcessMove(move1.DMove.toInt());
        
        //Delay for the move.
        delay(move1.DNum);
    }

}


void DanceMode()
{
    //We need to have a timer between commands.
    //If we dont get a new one after XX amount of time
    //We revert back to freeRange
    Serial.println("Backward");
    //Run(2);
}