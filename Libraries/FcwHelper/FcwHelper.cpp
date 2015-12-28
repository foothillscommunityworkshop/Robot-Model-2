#include "FcwHelper.h"
#include "Arduino.h"
#include "FcwServo.h"
#include "FcwRadio.h"
#include "ModeButton.h"
#include "PingSensor.h"
#include "PiezoBuzzer.h"
#include "FcwDebug.h"

//The distance from object before we change direction
const int TooClose = 300;
const int BeepCommand = 5;
int _debugLevel;

typedef  struct {
    String DMove; //Movement Id
    int DNum; //Delay for the movement
} DanceMove;

#define DanceListArray 3
#define DanceListMoves 7


// 0 = Just filler for delay,  1-4 = moves, 5 = beep
//const DanceMove  DMoves[] = {
//    {"0",2000},{"5", 500},{"1", 2000}, {"2",1500}, {"3",1500}, {"4",1500},{"5", 500}
//};

 DanceMove DanceMoveList[DanceListArray][DanceListMoves] = {
    {
        {"0",2000},{"5", 500},{"1", 2000}, {"2",1500}, {"3",1500}, {"4",1500},{"5", 500}
    },
    {
        {"0",2000},{"3", 500},{"4", 500}, {"1",200}, {"4",1000}, {"2",800},{"1", 500}
    },
    {
        {"0",2000},{"5", 500},{"3", 2000}, {"2",500}, {"4",1500}, {"3",1500},{"5", 500}
    },
};


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

    //Random number from 1-3 (tech 0-2)
    int randomDanceMove = (rand() % DanceListArray);
    
    //Convert string command to char* command to send.
    String command = String("B:"+ String(randomDanceMove));
    char* commandtoSend;
    command.toCharArray(commandtoSend, sizeof(command));
    
    //Send Command to the Slave bots
    bool sent = SendCommand(commandtoSend);
    
    //Process the dance move for the master
    DanceMoveProcessing(randomDanceMove);
 
    //Exit Master mode after the Dance is over
    
    ResetToStartUpMode();

}

void DanceMoveProcessing(int danceMoveItem)
{
    //Beep of entering the Dance Move process
    Beep(3);
    
    
    
    DebugOutput("DanceMoveItem:",String(danceMoveItem));
    
    for (int i; i < (sizeof(DanceMoveList[danceMoveItem])/sizeof(DanceMove)); i++)
    {
        DanceMove move1 = DanceMoveList[danceMoveItem][i];
        
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
    
    DanceMoveProcessing(GetMoveCommand());
    
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
    if(debugLevel >= _debugLevel)
    {
        if(_debugMode)
        {
            Serial.print(stringOutType);
            Serial.println(outputString);
        }
        
        if(CardStoreEnabled())
        {
            WriteToCard(stringOutType,outputString);
        }
        
                    
    }
 
}

void ResetToStartUpMode()
{
    
    DebugOutput("Reset to StartMode","",4);
    //Reset the robot back to startup mode.
    SetButtonCount(0); //Set button count to 0
    SetSlaveCommand("A"); //Set the Command to A which is Self Master.
   
}


