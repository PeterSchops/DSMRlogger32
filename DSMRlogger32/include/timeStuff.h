#ifndef TIMESTUFF_H
#define TIMESTUFF_H

//============ Includes ====================
#include "arduinoGlue.h"
#include <WString.h>

//-- Used in: processTelegram.cpp, timeStuff.cpp
// format: YYMMDDHHMMSS
String buildDateTimeString(const char *timeStamp, int len); 

// format: YYYY-MM-DD HH:MM:SS
String currentDateTimeString();

// number of minutes in current day (0..1439)
int currentMinutes();

//============ Added by Convertor ==========
#endif // TIMESTUFF_H
