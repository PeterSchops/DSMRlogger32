#ifndef TIMESTUFF_H
#define TIMESTUFF_H

//============ Includes ====================
#include "arduinoGlue.h"
#include <WString.h>

//-- Used in: DSMRlogger32.cpp, timeStuff.cpp
void logNtpTime();                                          
//-- Used in: DSMRlogger32.cpp, processTelegram.cpp, timeStuff.cpp
void saveTimestamp(const char *timeStamp);                  
//-- Used in: timeStuff.cpp, FSYSstuff.cpp
timeStruct buildTimeStruct(const char *timeStamp, uint16_t hourSlots , uint16_t daySlots , uint16_t monthSlots);
//-- Used in: timeStuff.cpp, FSYSstuff.cpp
timeStruct calculateTime(timeStruct useTime, int16_t units, int8_t ringType);
//-- Used in: processTelegram.cpp, timeStuff.cpp
// format: YYMMDDHHMMSS
String buildDateTimeString(const char *timeStamp, int len); 

// format: YYYY-MM-DD HH:MM:SS
String currentDateTimeString();

// number of minutes in current day (0..1439)
int currentMinutes();

#endif // TIMESTUFF_H
