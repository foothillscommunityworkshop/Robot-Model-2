#ifndef FcwHelper_h
#define FcwHelper_h
#include "Arduino.h"


void FreeRangeMode();
void MasterMode();
void DanceMode();
void DanceMoveProcessing();
void ResetToStartUpMode();
void DebugSetUp(bool setup);
void DebugOutput(String  stringOutType ,String outputString);
#endif