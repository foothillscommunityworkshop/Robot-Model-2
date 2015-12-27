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
const DanceMove DMoves[] = {{"1", 2000}, {"2",1500}, {"3",1500}, {"4",1500}};

bool _debugMode = false;

void FreeRangeMode()
{
    if (CurrentDuration() < TooClose)
    {
        Beep(1);
        
        //Avoid Obstacle()
        AvoidObstacle();
        
        DebugOutput("AvoidObstacle","");
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

    //Send Command to the Slave bots
    bool sent = SendCommand("B");
    
    DanceMoveProcessing();
 

    //Exit Master mode after the Dance is over
    ResetToStartUpMode();

}

void DanceMoveProcessing()
{
    //Beep of entering the Dance Move process
    Beep(3, 300);
    for (int i; i < 4; i++)
    {
        DanceMove move1 = DMoves[i];
        ProcessMove(move1.DMove.toInt());
        delay(move1.DNum);
    }
    
    //Beep on exiting the dancing moves process
    Beep(6, 300);
}

void DanceMode()
{
    DebugOutput("DanceMove Moving","");
    
    DanceMoveProcessing();
    
    ResetToStartUpMode();
  
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
    SetButtonCount(0);
    SetSlaveCommand("A");
   
}


