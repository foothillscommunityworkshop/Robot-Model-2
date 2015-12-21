#include <FcwRadio.h>
#include <SPI.h>
#include <NRF24.h>
//#include <Arduino.h>

//volatile

NRF24 radio;


const int radioInterrupt = 1; //This tranlates to Pin 3
volatile bool isSlaveMode = false;
 String slaveCommand;


void check_radio()
{
    uint8_t oldSREG = SREG;
    cli ();
    if (radio.available())
    {
        char buf[32];
        uint8_t numBytes = radio.read(buf, sizeof(buf));
        
        //Need to figure out what we need to do here for the output. 
        String TempString = String(buf);
        slaveCommand = ( String)TempString;
        
        //slaveCommand[0] = buf[1];
        
    }
   // sei ();
    SREG = oldSREG;
}

void SetSlaveCommand(char* command)
{
    slaveCommand[0] = command[0];
}

String GetSlaveCommand()
{
    return slaveCommand;
}

bool SendCommand(char* command)
{
    detachInterrupt(radioInterrupt);
    bool sent = radio.send(0xD2, command);
    return sent;
}


void RadioSetup(int cePin, int csPin)
{
    radio.begin(cePin, csPin);
    radio.setAddress(0xD2);
    radio.startListening();
    attachInterrupt(radioInterrupt, check_radio, LOW);
}

