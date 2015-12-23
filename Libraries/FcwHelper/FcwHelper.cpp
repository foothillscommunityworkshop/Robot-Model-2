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
    //Beep Enter master mode
  //  Beep(3);
    
    DebugOutput("Enter MasterMode","");

    //Send Command to the Slave bots
    bool sent = SendCommand("B");
    
    DanceMoveProcessing();

    //Beep to show leaving Master Mode
   // Beep(6);
 

    
    
    //Exit Master mode after the Dance is over
    ResetToStartUpMode();

}

void DanceMoveProcessing()
{
    Beep(3);
    for (int i; i < 4; i++)
    {
        DanceMove move1 = DMoves[i];
        ProcessMove(move1.DMove.toInt());
        delay(move1.DNum);
    }
    Beep(6);
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


