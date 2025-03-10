#ifndef FSYSSTUFF_H
#define FSYSSTUFF_H

//============ Includes ====================

enum class RingType
{
  NONE = 0,
  HOURS = 1,
  DAYS = 2,
  MONTHS = 3,
  YEARS = 4,
};

//-- Used in: DSMRlogger32.cpp, FSYSstuff.cpp
void readLastStatus();                                      
//-- Used in: DSMRlogger32.cpp, restAPI.cpp, FSYSstuff.cpp, menuStuff.cpp, processTelegram.cpp
void writeLastStatus();                                     
//-- Used in: processTelegram.cpp, FSYSstuff.cpp
void buildDataRecordFromSM(char *recIn, timeStruct useTime);
//-- Used in: restAPI.cpp, FSYSstuff.cpp
uint16_t buildDataRecordFromJson(char *recIn, int recLen, String jsonIn);
//-- Used in: restAPI.cpp, processTelegram.cpp, FSYSstuff.cpp
void writeDataToRingFile(char *fileName, RingType ringType, char *record, timeStruct slotTime);
//-- Used in: FSYSstuff.cpp, restAPI.cpp, menuStuff.cpp
void writeDataToRingFiles(timeStruct useTime);              
//-- Used in: FSYSstuff.cpp, menuStuff.cpp
void readAllSlots(char *record, RingType ringType, const char *fileName, timeStruct thisTime);
//-- Used in: settingsStuff.cpp, FSYSstuff.cpp
bool alterRingFile();                                       
//-- Used in: settingsStuff.cpp, FSYSstuff.cpp
uint16_t readRingHistoryDepth(const char *fileName, RingType ringType);
//-- Used in: FSYSstuff.cpp, menuStuff.cpp
void listFilesystem();                                      
//-- Used in: FSYSstuff.cpp, menuStuff.cpp
void eraseFile();                                           
//-- Used in: DSMRsetupStuff.cpp, FSYSstuff.cpp
bool DSMRfileExist(const char *fileName, const char* funcName, bool doDisplay);


//=========== Prototypes ==================
void fillRecord(char *record, int8_t maxLen);               
int32_t freeSpace();                                        
bool createRingFile(const char *fileName, timeStruct useTime, RingType ringType);
bool createRingFile(const char *fileName, timeStruct useTime, RingType ringType, uint16_t noSlots);
int sortListFiles(const void *cmp1, const void *cmp2);      

#endif // FSYSSTUFF_H
