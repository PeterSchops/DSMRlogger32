#ifndef RESTAPI_H
#define RESTAPI_H

//============ Includes ====================
#include "arduinoGlue.h"
#include "Shield32.h"
#include "FSYSstuff.h"

DECLARE_TIMER_EXTERN(antiWearTimer);
   
//============ Prototypes ==================
void processApiV2Sm(const char* apiId, const char* oneField);
void processApiV2Dev(const char *URI, const char *apiId, const char *word5, const char *word6);
void processApiV2Shield(const char *URI, const char *apiId, const char *word5, const char *word6);
void processApiV2Hist(const char *URI, const char *apiId, const char *word5, const char *word6);
void sendDeviceInfo();
void sendDeviceTime();                                      
void sendDevSettings();                                     
void sendSMsettings();   
void sendShieldSettings();   
void sendDeviceDebug(const char *URI, String tail);         
void sendShieldInfo();
void sendJsonV2smApi(const char *firstLevel);               
void sendJsonActualHist();                                  
void sendJsonHist(RingType ringType, const char *fileName, timeStruct useTime, uint8_t limit, bool sortDesc);
void listFieldsArray(char inArray[][35]);                   
void sendApiNotFound(const char *URI);                      
//-- Used in: DSMRlogger32.cpp, restAPI.cpp
bool isInFieldsArray(const char *lookUp, int elemts);       

#endif // RESTAPI_H
