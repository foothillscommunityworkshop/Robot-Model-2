#ifndef FcwDebug_h
#define FcwDebug_h
#include "Arduino.h"

void SDCardSetup(int chipSelect , bool storeToCard);
void WriteToCard(String  stringOutType ,String outputString);
bool CardStoreEnabled();
#endif