#include "FcwHelper.h"
#include "Arduino.h"
#include "FcwServo.h"
#include "FcwRadio.h"
#include "ModeButton.h"
#include "PingSensor.h"
#include "PiezoBuzzer.h"

//The distance from object before we change direction
const int TooClose = 300;

typedef  struct {
    String DMove;
    int DNum;
} DanceMove;
const DanceMove DMoves[] = {{"1", 1000}, {"2",500}, {"3",1500}, {"4",1500}};

long DanceStartTime;
long DanceDiffTime;
int TIMEOUT = 3000;
bool _debugMode = false;

void FreeRangeMode()
{
    if (CurrentDuration() < TooClose)
    {
        //Turn Random
        TurnRandom();
        Beep(1);
        
        DebugOutput("Turn","");
        DebugOutput("Dur:",String(CurrentDuration()));
    }
    else
    {
        //Run straight
        Run(1);
        DebugOutput("Run","");
        DebugOutput("Dur:",String(CurrentDuration()));
    }
}




void MasterMode()
{
    DebugOutput("Enter MasterMode","");
    for (int i; i < 4; i++)
    {
        DanceMove move1 = DMoves[i];
        
        //B = slave mode
        String command = "B:";
        command.concat(move1.DMove);
        
        char commandToSend[command.length() + 1];
        command.toCharArray(commandToSend, command.length() + 1);
        
        DebugOutput("Master Command To send:",String(commandToSend));
        //Send Command to the Slave bots
        SendCommand(commandToSend);
        
        DebugOutput("Master, command to process:",move1.DMove);
        //Process the Command ourself
        ProcessMove(move1.DMove.toInt());
        
        DebugOutput("Master command delay:",String(move1.DNum));
        //Delay for the move.
        delay(move1.DNum);
    }
    

    //Exit Master mode after the Dance is over
    ResetToStartUpMode();

}


void DanceMode(int move)
{
    //We need to have a timer between commands.
    //If we dont get a new one after XX amount of time
    //We revert back to freeRange
    long currentTime = millis();
    
    DanceDiffTime = currentTime - DanceStartTime;
    
    //If we are not timeouted sense the last command.
    if(DanceDiffTime < TIMEOUT)
    {
        ProcessMove(move);
        DanceStartTime = currentTime;
    }
    else
    {
        ResetToStartUpMode();
    }
   
    
}

void DebugSetUp(bool setup)
{
    if(setup)
    {
        _debugMode = setup;
        Serial.begin (115200);
    }
}

void DebugOutput(String  stringOutType ,String outputString)
{
    if(_debugMode)
    {
        Serial.print(stringOutType);
        Serial.println(outputString);
    }
 
}

void ResetToStartUpMode()
{
    DebugOutput("Reset to StartMode","");
    //Reset the robot back to startup mode.
    DanceDiffTime = 0;
    SetButtonCount(0);
    SetSlaveCommand("A");

}


