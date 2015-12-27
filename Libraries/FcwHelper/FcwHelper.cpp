#include "FcwHelper.h"
#include "Arduino.h"
#include "FcwServo.h"
#include "FcwRadio.h"
#include "ModeButton.h"
#include "PingSensor.h"
#include "PiezoBuzzer.h"

//The distance from object before we change direction
const int TooClose = 300;
const int BeepCommand = 5;
int _debugLevel;

typedef  struct {
    String DMove; //Movement Id
    int DNum; //Delay for the movement
} DanceMove;

// 0 = Just filler for delay,  1-4 = moves, 5 = beep
const DanceMove DMoves[] = {{"0",2000},{"5", 500},{"1", 2000}, {"2",1500}, {"3",1500}, {"4",1500},{"5", 500}};

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
    
    //Process the dance move for the master
    DanceMoveProcessing();
 
    //Exit Master mode after the Dance is over
    ResetToStartUpMode();

}

void DanceMoveProcessing()
{
    //Beep of entering the Dance Move process
    Beep(3);
    
    for (int i; i < (sizeof(DMoves)/sizeof(DanceMove)); i++)
    {
        DanceMove move1 = DMoves[i];
        
        //We only looking for movement Int's from 1-4 for movement
        if(move1.DMove.toInt() > 0 && move1.DMove.toInt() <= 4)
        {
            ProcessMove(move1.DMove.toInt());
        }
        else if(move1.DMove.toInt() == BeepCommand) //5 repersents a beep command
        {
            Beep(1);
        }
        delay(move1.DNum);
    }
    
    //Beep on exiting the dancing moves process
    Beep(3);
}

void DanceMode()
{
    DebugOutput("DanceMove Moving","");
    
    DanceMoveProcessing();
    
    ResetToStartUpMode();
  
}

void DebugSetUp(bool setup, int debugLevel)
{
    if(setup)
    {
        _debugMode = setup;
        Serial.begin (115200);
    }
    
    _debugLevel = debugLevel;
    
    
}

void DebugOutput(String  stringOutType ,String outputString, int debugLevel)
{
    if(_debugMode && debugLevel >= _debugLevel)
    {
        Serial.print(stringOutType);
        Serial.println(outputString);
    }
 
}

void ResetToStartUpMode()
{
    
    DebugOutput("Reset to StartMode","",4);
    //Reset the robot back to startup mode.
    SetButtonCount(0); //Set button count to 0
    SetSlaveCommand("A"); //Set the Command to A which is Self Master.
   
}


