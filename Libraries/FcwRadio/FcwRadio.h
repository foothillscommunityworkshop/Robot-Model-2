#ifndef FcwRadio_h
#define FcwRadio_h
#include <Arduino.h>

void RadioSetup(int cePin, int csPin);
bool SendCommand(char* command);

String GetSlaveCommand();
void SetSlaveCommand(String command);
String GetMoveCommand();

#endif