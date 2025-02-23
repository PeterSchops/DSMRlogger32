#ifndef HELPERSTUFF_H
#define HELPERSTUFF_H

//============ Includes ====================
#include "arduinoGlue.h"

DECLARE_TIMER_EXTERN(publishMQTTtimer);

//-- Used in: FSmanager.cpp, restAPI.cpp, DSMRlogger32.cpp
void processAPI();                                          
//-- Used in: restAPI.cpp, helperStuff.cpp
void copyToFieldsArray(const char inArray[][35], int elemts);
//-- from networkStuff.ino -----------
//-- Used in: DSMRlogger32.cpp, networkStuff.cpp, menuStuff.cpp
void startWiFi(const char *hostname, int timeOut, bool eraseCredentials);
//-- Used in: DSMRlogger32.cpp, networkStuff.cpp
void startTelnet();                                         
//-- Used in: DSMRlogger32.cpp, settingsStuff.cpp, networkStuff.cpp
void startMDNS(const char *Hostname);                       
//-- from helperStuff.ino -----------
//-- Used in: DSMRlogger32.cpp, networkStuff.cpp, FSYSstuff.cpp, FSmanager.cpp, helperStuff.cpp
void pulseHeart(bool force);                                
//-- Used in: DSMRlogger32.cpp, networkStuff.cpp, FSYSstuff.cpp, FSmanager.cpp, helperStuff.cpp
void pulseHeart();                                          
//-- Used in: DSMRlogger32.cpp, helperStuff.cpp, networkStuff.cpp, menuStuff.cpp
void resetWatchdog();                                       
//-- Used in: helperStuff.cpp, MQTTstuff.cpp
boolean isValidIP(IPAddress ip);                            
//-- Used in: restAPI.cpp, helperStuff.cpp, FSYSstuff.cpp
bool isValidTimestamp(const char *timeStamp, int8_t len);   
//-- Used in: restAPI.cpp, helperStuff.cpp
int8_t splitString(String inStrng, char delimiter, String wOut[], uint8_t maxWords);
//-- Used in: DSMRlogger32.cpp, restAPI.cpp, helperStuff.cpp, menuStuff.cpp
String upTime();                                            
//-- Used in: helperStuff.cpp, timeStuff.cpp, FSYSstuff.cpp
void strCpyFrm(char *dest, int maxLen, const char *src, uint8_t frm, uint8_t to);
//-- Used in: DSMRlogger32.cpp, helperStuff.cpp
float strToFloat(const char *s, int dec);                   
//-- Used in: helperStuff.cpp, MQTTstuff.cpp
double round1(double value);                                
//-- Used in: helperStuff.cpp
double round2(double value);                                
//-- Used in: restAPI.cpp, helperStuff.cpp, MQTTstuff.cpp
double round3(double value);                                
//-- Used in: DSMRlogger32.cpp, helperStuff.cpp
void getLastResetReason(RESET_REASON reason, char *txtReason, int txtReasonLen);
//-- Used in: handleTestdata.cpp, restAPI.cpp, helperStuff.cpp, handleSlimmeMeter.cpp
unsigned int CRC16(unsigned int crc, unsigned char *buf, int len);


//-- Used in: DSMRlogger32.cpp, restAPI.cpp, helperStuff.cpp, MQTTstuff.cpp
void addToTable(const char *cName, const char *cValue);     
//-- Used in: DSMRlogger32.cpp, restAPI.cpp, helperStuff.cpp, MQTTstuff.cpp
void addToTable(const char *cName, String sValue);          
//-- Used in: DSMRlogger32.cpp, restAPI.cpp, helperStuff.cpp, MQTTstuff.cpp
void addToTable(const char *cName, uint32_t uValue);        
//-- Used in: DSMRlogger32.cpp, restAPI.cpp, helperStuff.cpp, MQTTstuff.cpp
void addToTable(const char *cName, int32_t iValue);         
//-- Used in: DSMRlogger32.cpp, restAPI.cpp, helperStuff.cpp, MQTTstuff.cpp
void addToTable(const char *cName, float fValue);           
//-- Used in: DSMRlogger32.cpp, helperStuff.cpp
void pushToActualStore(const char *cName, String sValue);   
//-- Used in: DSMRlogger32.cpp, helperStuff.cpp
void pushToActualStore(const char *cName, float fValue);    
//-- Used in: helperStuff.cpp, processTelegram.cpp
void pushTlgrmToActualStore();                              


struct buildJsonV2ApiSm
{
  bool  skip = false;

  template<typename Item>
  void apply(Item &i)
  {
    skip = false;
    String Name = String(Item::name);
    if (!isInFieldsArray(Name.c_str(), fieldsElements)) {
      skip = true;
    }
    if (!skip) {
      if (i.present()) {
        addToTable(Name.c_str(), typecastValue(i.val()));
      }
    }
  }
};


struct addSmToActualStore
{
  bool  skip = false;

  template<typename Item>
  void apply(Item &i) {
    skip = false;
    String Name = String(Item::name);
    if (!isInFieldsArray(Name.c_str(), fieldsElements)) {
      skip = true;
    }
    if (!skip) {
      if (i.present()) {
        pushToActualStore(Name.c_str(), typecastValue(i.val()));
      }
    }
  }
};

struct SpiRamAllocator 
{
  void* allocate(size_t size) {
    return heap_caps_malloc(size, MALLOC_CAP_SPIRAM);
  }

  void deallocate(void* pointer) {
    heap_caps_free(pointer);
  }

  void* reallocate(void* ptr, size_t new_size) {
    return heap_caps_realloc(ptr, new_size, MALLOC_CAP_SPIRAM);
  }
};

using SpiRamJsonDocument = BasicJsonDocument<SpiRamAllocator>;

#endif // HELPERSTUFF_H
