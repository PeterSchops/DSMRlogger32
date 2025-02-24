#ifndef ARDUINOGLUE_H
#define ARDUINOGLUE_H


//============ Includes ====================
#include <SSD1306Ascii.h>
#include <SSD1306AsciiWire.h>
#include <WiFi.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <WiFiManager.h>
#include <FS.h>
#include <esp_heap_caps.h>
#include <SPIFFS_SysLogger.h>
#include <HardwareSerial.h>
#include <rom/rtc.h>
#include <HTTPUpdateServer.h>
#include <TelnetStream.h>
#include <ArduinoJson.h>
#include <dsmr2.h>
#include <PubSubClient.h>
#include <TimeSyncLib.h>
#include "safeTimers.h"
#include "Debug.h"

//============ Defines & Macros====================


#define _SPIFFS
#define _FSYS SPIFFS

#define writeToSysLog(...) ({ \
        time_t now = time(NULL);   \
        struct tm  tstruct; \
        localtime_r(&now, &tstruct); \
        sysLog.writeDbg(sysLog.buildD("[%04d-%02d-%02d %02d:%02d:%02d][%-12.12s] ",  \
                             tstruct.tm_year+1900,       \
                             tstruct.tm_mon+1,           \
                             tstruct.tm_mday,            \
                             tstruct.tm_hour,            \
                             tstruct.tm_min,             \
                             tstruct.tm_sec,             \
                             __FUNCTION__),              \
                             ##__VA_ARGS__);             \
                           })

const uint16_t _SYSLOG_LINES = 150;
const size_t _SYSLOG_LINE_LEN = 120;
#define AMSTERDAM_POSIX "CET-1CEST,M3.5.0,M10.5.0/3" // Time in Amsterdam
#define  tmYearToCalendar(Y) ((Y) + 1970)  // full four digit year 
#define  CalendarYrToTm(Y)   ((Y) - 1970)
#define _DEFAULT_HOSTNAME     "DSMR-ESP32"
#define _REMOTE_UPDATESERVER  "https://www.aandewiel.nl/updates/DSMRlogger32/"


#ifdef ESP32_WROVER
#define _NEO_PIN                23    //                 hardware
//#define RST_PIN -1
#define SMRX                    18    //                 hardware                  
#define SMTX                    -1    //                 hardware
#define _PIN_WD_RESET            0    //-- GPIO00        hardware
#define _PIN_HEARTBEAT           4    //                 hardware
#define _DTR_ENABLE              5    //                 hardware
#define LED_BUILTIN             15    //-- esp32         hardware
#define _FLASH_BUTTON            0
#else //ESP32 S2 mini
#define _NEO_PIN                18    //                 hardware
//#define RST_PIN -1
#define SMRX                    37    //   GPIO37        hardware data in, can be any IO               
#define SMTX                    -1    //                 hardware
#define _PIN_WD_RESET            0    //-- GPIO00        hardware
#define _PIN_HEARTBEAT           3    //                 hardware alive pulses for WD
#define _DTR_ENABLE              5    //                 hardware request data frame
#define LED_BUILTIN             15    //-- GPIO15        hardware
//      SDA                                GPIO08        hardware for OLED display
//      SCL                                GPIO09        hardware for OLED display
#define _FLASH_BUTTON            0
#endif
const int _SHIELD_TIME = 10;
const size_t _TLGRM_LEN = 10000;      //-- probably a bit to long
const size_t _JSONBUFF_LEN = 220000;  //-- 60000 is needed for 190 Hour History
const size_t _GMSG_LEN = 512;
const size_t _FCHAR_LEN = 50;
const size_t _HOSTNAME_LEN = 30;
const size_t _INDEXPAGE_LEN = 50;
const size_t _MQTT_BROKER_LEN = 101;
const size_t _MQTT_USER_LEN = 40;
const size_t _MQTT_PASSWD_LEN = 40;
const size_t _MQTT_TOPTOPIC_LEN = 21;
#define _SETTINGS_FILE        "/DSMRsmSettings.json"
#define _SYSTEM_FILE          "/DSMRdevSettings.json"
#define _SHIELD_FILE          "/DSMRShieldSettings.json"
#define _STATUS_FILE          "/DSMRstatus.csv"
#define LED_ON                 LOW
#define LED_OFF               HIGH
#define _GLOW_TIME             300 //ms

const int _FSYS_MAX_FILES = 30;
// #define _MQTT_BUFF_MAX         200
const size_t _TIMESTAMP_LEN = 14; // yymmddhhmmssX\0
const size_t _PSRAM_LIMIT = 100;
enum ringType
{
  RNG_HOURS = 1,
  RNG_DAYS = 2,
  RNG_MONTHS = 3,
  RNG_YEARS = 4,
};

#define DATA_FORMAT "%-8.8s;%10.3f;%10.3f;%10.3f;%10.3f;%10.3f;%10.3f;"
#define DATA_CSV_HEADER   "YYMMDDHH;      EDT1;      EDT2;      ERT1;      ERT2;       GDT;       WDT;#%5d"
const size_t DATA_RECLEN = 83; //-- compatible with reclen API firmware
#define HOURS_FILE        "/RINGhours.csv"
const uint16_t _NO_HOUR_SLOTS_ = (48 + 1);
#define DAYS_FILE "/RINGdays.csv"
const uint16_t _NO_DAY_SLOTS_ = (14 + 1);
#define MONTHS_FILE "/RINGmonths.csv"
const uint16_t _NO_MONTH_SLOTS_ = (24 + 1);
const uint16_t _MAX_ACTUAL_STORE = 500; // linked with _JSONBUFF_LEN

//-- from DSMRlogger32.h
const size_t _MY_SSID_LEN   = 100;
const size_t _MY_PASSWD_LEN = 100;
struct myWiFiStruct
{
  char      SSID[_MY_SSID_LEN];
  char      password[_MY_PASSWD_LEN];
  IPAddress ipWiFi; 
  IPAddress ipGateway;
  IPAddress ipDNS; 
  IPAddress ipSubnet;
};

//-- from DSMRlogger32.h
const size_t _FIELDTABLE_CVALUE_LEN = 100;
union t
{
  char      cValue[_FIELDTABLE_CVALUE_LEN];
  int32_t   iValue;
  uint32_t  uValue;
  float     fValue;
};

//-- from DSMRlogger32.h
const size_t _FIELDTABLE_CNAME_LEN = 100;
struct fieldTableStruct
{
  char      cName[_FIELDTABLE_CNAME_LEN];
  t         type;
  char      cType;
};

//-- from DSMRlogger32.h
struct settingSmStruct
{
  uint8_t   PreDSMR40;
  uint8_t   SmHasFaseInfo;
  uint8_t   Mbus1Type;
  uint8_t   Mbus2Type;
  uint8_t   Mbus3Type;
  uint8_t   Mbus4Type;
  float     EDT1;
  float     EDT2;
  float     ERT1;
  float     ERT2;
  float     GDT; //gas delivered
  float     WDT; //water delivered
  float     ENBK;
  float     GNBK;//gas network cost
  float     WNBK;//water network cost
};

//-- from DSMRlogger32.h
struct settingDevStruct
{
  char      Hostname[_HOSTNAME_LEN];
  char      IndexPage[_INDEXPAGE_LEN];
  uint8_t   TelegramInterval;
  uint8_t   OledType;    // 0=none, 1=SSD1306, 2=SH1106
  uint16_t  OledSleep;
  uint8_t   OledFlip;
  uint8_t   NeoBrightness;
  uint8_t   DailyReboot;
  uint8_t   runAPmode;
  uint16_t  NoHourSlots;
  uint16_t  NoDaySlots;
  uint16_t  NoMonthSlots;
  char      MQTTbroker[_MQTT_BROKER_LEN];
  char      MQTTuser[_MQTT_USER_LEN];
  char      MQTTpasswd[_MQTT_PASSWD_LEN];
  char      MQTTtopTopic[_MQTT_TOPTOPIC_LEN];
  int32_t   MQTTinterval;
  int16_t   MQTTbrokerPort;
};

struct settingShieldStruct
{
  int8_t    GPIOpin;      //-- only -1, 13 or 14
  int8_t    inversed;
  uint16_t  activeStart;  //-- minuten
  uint16_t  activeStop;   //-- minuten
  int16_t   onThreshold;
  int16_t   offThreshold;
  int32_t   onDelay;      //-- seconden
  int32_t   offDelay;     //-- seconden
};

//-- from DSMRlogger32.h
struct actualDataStruct
{
  uint32_t  count;
  char      timestamp[_TIMESTAMP_LEN+1];
  float     power_delivered_l1;
  float     power_delivered_l2;
  float     power_delivered_l3;
  float     power_returned_l1;
  float     power_returned_l2;
  float     power_returned_l3;
  float     gas_delivered;//gas
  float     water_delivered;//water
  uint8_t   relay_state;  //-- 1=on, 0=off
};

//-- from DSMRlogger32.h
struct timeStruct
{
  char      Timestamp[_TIMESTAMP_LEN];
  int16_t   Year;
  int8_t    Month;
  int8_t    Day;
  int8_t    Hour;
  int8_t    Minute;
  int8_t    Second;
  int8_t    Weekday;    //--  1 = Sunday
  time_t    epoch;
  uint32_t  Months;     //-- Months since epoch
  uint16_t  monthsHist; //-- number of slots per month
  uint16_t  monthSlot;  //-- active month slot
  uint32_t  Days;       //-- Days since epoch
  uint16_t  daysHist;   //-- number of slots per day
  uint16_t  daySlot;    //-- active day slot
  uint32_t  Hours;      //-- Hours since epoch
  uint16_t  hoursHist;  //-- number of slots per hour
  uint16_t  hourSlot;   //-- active hour slot
};




//-- from FSYSstuff.ino
struct listFileStruct
{
  char    Name[32];
  int32_t Size;
};

//-- from DSMRlogger32.ino
struct showValues
{
  template<typename Item>
  void apply(Item &i) {
    if (i.present()) {
      DebugT(Item::name);
      Debug(F(": "));
      Debug(i.val());
      Debug(Item::unit());
    }
    Debugln();
  }
};


//=======================================================================
//TODO move to DSMRlogger.h 
template<typename Item>
Item &typecastValue(Item &i)
{
  return i;
}




extern int fieldsElements; //-- from restAPI

using MyData = ParsedData<
              identification,              /* String */
              p1_version,                  /* String */ 
              p1_version_be,               /* String 0-0:96.1.4(50221) */
              // grid_configuration,          /* String 1-0:94.32.1(400) */
              timestamp,                   /* String 0-0:1.0.0(250219234430W) */
              equipment_id,                /* String 0-0:96.1.1() */
              peak_pwr_last_q,             /* FixedValue 1-0:1.4.0() */
              highest_peak_pwr,            /* TimestampedFixedValue 1-0:1.6.0() */
              energy_delivered_tariff1,    /* FixedValue 1-0:1.8.1(000224.375*kWh) */
              energy_delivered_tariff2,    /* FixedValue 1-0:1.8.2(000361.948*kWh) */ 
              energy_returned_tariff1,     /* FixedValue 1-0:2.8.1(000172.963*kWh) */
              energy_returned_tariff2,     /* FixedValue 1-0:2.8.2(000082.945*kWh) */
              electricity_tariff,          /* String 0-0:96.14.0(0002) */
              power_delivered,             /* FixedValue 1-0:1.7.0(00.378*kW) */ 
              power_returned,              /* FixedValue 1-0:2.7.0(00.000*kW) */
              electricity_threshold,       /* FixedValue */
              electricity_switch_position, /* uint8_t */
              // electricity_failures,        /* uint32_t */
              // electricity_long_failures,   /* uint32_t */
              // electricity_failure_log,     /* String */
              // electricity_sags_l1,         /* uint32_t */
              // electricity_sags_l2,         /* uint32_t */ 
              // electricity_sags_l3,         /* uint32_t */
              // electricity_swells_l1,       /* uint32_t */
              // electricity_swells_l2,       /* uint32_t */ 
              // electricity_swells_l3,       /* uint32_t */
              message_short,               /* String */
              // message_long              /* String this one is too big and will crash the MCU */
              voltage_l1,                  /* FixedValue 1-0:32.7.0(239.2*V) */
              voltage_l2,                  /* FixedValue 1-0:52.7.0(240.3*V) */
              voltage_l3,                  /* FixedValue 1-0:72.7.0(240.9*V) */
              current_l1,                  /* FixedValue 1-0:31.7.0(000.32*A) */
              current_l2,                  /* FixedValue 1-0:51.7.0(000.55*A) */
              current_l3,                  /* FixedValue 1-0:71.7.0(000.99*A) */
              power_delivered_l1,          /* FixedValue 1-0:21.7.0(00.061*kW) */
              power_delivered_l2,          /* FixedValue 1-0:41.7.0(00.112*kW) */
              power_delivered_l3,          /* FixedValue 1-0:61.7.0(00.205*kW) */
              power_returned_l1,           /* FixedValue 1-0:22.7.0(00.000*kW) */
              power_returned_l2,           /* FixedValue 1-0:42.7.0(00.000*kW) */
              power_returned_l3,           /* FixedValue 1-0:62.7.0(00.000*kW) */
              //electricity_switch_position, /* uint8_t 0-0:96.3.10(1) */
              //electricity_threshold,       /* FixedValue  0-0:17.0.0(99.999*kW) */
              mbus1_device_type,           /* uint16_t 0-1:24.1.0(003) */
              mbus1_equipment_id_tc,       /* String */
              mbus1_equipment_id_ntc,      /* String 0-1:96.1.1(37414D5832313234323038373434) */
              mbus1_valve_position,        /* uint8_t 0-1:24.4.0(1) */
              mbus1_delivered,             /* TimestampedFixedValue */
              mbus1_delivered_ntc,         /* TimestampedFixedValue 0-1:24.2.3(250219234154W)(00000.014*m3) */
              mbus1_delivered_dbl,         /* TimestampedFixedValue */
              mbus2_device_type,           /* uint16_t 0-2:24.1.0(007) */
              mbus2_equipment_id_tc,       /* String */
              mbus2_equipment_id_ntc,      /* String 0-2:96.1.1(3853455430303130323038353939) */
              mbus2_valve_position,        /* uint8_t */
              mbus2_delivered,             /* TimestampedFixedValue 0-2:24.2.1(250219233900W)(00000.542*m3) */
              mbus2_delivered_ntc,         /* TimestampedFixedValue */
              mbus2_delivered_dbl,         /* TimestampedFixedValue */
              mbus3_device_type,           /* uint16_t */
              mbus3_equipment_id_tc,       /* String */
              mbus3_equipment_id_ntc,      /* String */
              mbus3_valve_position,        /* uint8_t */
              mbus3_delivered,             /* TimestampedFixedValue */
              mbus3_delivered_ntc,         /* TimestampedFixedValue */
              mbus3_delivered_dbl,         /* TimestampedFixedValue */
              mbus4_device_type,           /* uint16_t */
              mbus4_equipment_id_tc,       /* String */
              mbus4_equipment_id_ntc,      /* String */
              mbus4_valve_position,        /* uint8_t */
              mbus4_delivered,             /* TimestampedFixedValue */
              mbus4_delivered_ntc,         /* TimestampedFixedValue */
              mbus4_delivered_dbl          /* TimestampedFixedValue */
              >;


//============ Extern Variables ============
//-- used in DSMRlogger32.cpp, settingsStuff.cpp
extern const char*     _FW_VERSION;                           //-- from DSMRlogger32.cpp
//-- used in DSMRlogger32.cpp
extern PubSubClient    MQTTclient;                        		//-- from DSMRlogger32
//-- used in DSMRlogger32.cpp, MQTTstuff.cpp, restAPI.cpp, menuStuff.cpp, FSYSstuff.cpp, FSmanager.cpp, settingsStuff.cpp
extern bool            Verbose1;                          		//-- from DSMRlogger32
//-- used in handleTestdata.cpp, MQTTstuff.cpp, restAPI.cpp, menuStuff.cpp, FSYSstuff.cpp, handleSlimmeMeter.cpp
extern bool            Verbose2;                          		//-- from DSMRlogger32
//-- used in helperStuff.cpp
extern int             actualElements;                    		//-- from DSMRlogger32
//-- used in helperStuff.cpp
extern uint32_t        actualStoreCount;                  		//-- from DSMRlogger32
//-- used in helperStuff.cpp
extern uint16_t        actualStoreSlot;                   		//-- from DSMRlogger32
extern char            actualTableArray[][35];
extern char            actualArray[][35];
extern char            infoArray[][35];
extern bool            boolDisplay;                       		//-- from DSMRlogger32
extern bool            buttonState;                       		//-- from DSMRlogger32
//-- used in DSMRlogger32.cpp, helperStuff.cpp, DSMRsetupStuff.cpp
extern bool            filesysMounted;                    		//-- from DSMRlogger32
//-- used in handleTestdata.cpp, DSMRlogger32.cpp, networkStuff.cpp, MQTTstuff.cpp, restAPI.cpp, menuStuff.cpp, FSYSstuff.cpp, FSmanager.cpp, settingsStuff.cpp, processTelegram.cpp, helperStuff.cpp, DSMRsetupStuff.cpp, handleSlimmeMeter.cpp
extern const char*     flashMode[];                       		//-- from DSMRlogger32
//-- used in handleTestdata.cpp, restAPI.cpp, FSYSstuff.cpp, helperStuff.cpp, handleSlimmeMeter.cpp
extern float           gasDelivered;                      		//-- from DSMRlogger32
extern float           waterDelivered;                    		//-- from DSMRlogger32
extern float           peakPowerCurrentQuarter;
extern float           peakPowerCurrentMonth;
//-- used in helperStuff.cpp
extern uint32_t        glowTimer0;                        		//-- from DSMRlogger32
//-- used in DSMRlogger32.cpp, handleSlimmeMeter.cpp, FSYSstuff.cpp
extern uint32_t        glowTimer1;                        		//-- from DSMRlogger32
//-- used in DSMRlogger32.cpp
extern bool            hasAlternativeIndex;               		//-- from DSMRlogger32
//-- used in DSMRlogger32.cpp, networkStuff.cpp
extern HTTPUpdateServer httpUpdater;                       		//-- from DSMRlogger32
extern int             infoElements;                      		//-- from DSMRlogger32
//-- used in DSMRlogger32.cpp
extern char            lastResetCPU0[100];                		//-- from DSMRlogger32
//-- used in DSMRlogger32.cpp
extern char            lastResetCPU1[100];                		//-- from DSMRlogger32
//-- used in handleTestdata.cpp, DSMRlogger32.cpp, restAPI.cpp, menuStuff.cpp, FSYSstuff.cpp, processTelegram.cpp
extern timeStruct      lastTlgrmTime;                     		//-- from DSMRlogger32
//-- used in settingsStuff.cpp, restAPI.cpp
extern bool            mqttIsConnected;                   		//-- from DSMRlogger32
//-- used in DSMRlogger32.cpp
extern uint8_t         msgMode;                           		//-- from DSMRlogger32
//-- used in DSMRlogger32.cpp, FSYSstuff.cpp, menuStuff.cpp
extern uint32_t        nrReboots;                         		//-- from DSMRlogger32
//-- used in DSMRlogger32.cpp
extern uint8_t         ntpEventId;                        		//-- from DSMRlogger32
//-- used in restAPI.cpp, helperStuff.cpp
extern bool            onlyIfPresent;                     		//-- from DSMRlogger32
//-- used in processTelegram.cpp, FSYSstuff.cpp
extern timeStruct      prevTlgrmTime;                     		//-- from DSMRlogger32
//-- used in DSMRlogger32.cpp, settingsStuff.cpp, menuStuff.cpp
extern bool            runAPmode;                         		//-- from DSMRlogger32
//-- used in menuStuff.cpp
extern bool            showRaw;                           		//-- from DSMRlogger32
//-- used in menuStuff.cpp
extern int8_t          showRawCount;                      		//-- from DSMRlogger32
//-- used in helperStuff.cpp
extern bool            skipHeartbeats;                    		//-- from DSMRlogger32
//-- used in DSMRlogger32.cpp
extern P1Reader        slimmeMeter;                       		//-- from DSMRlogger32
//-- used in DSMRlogger32.cpp, FSYSstuff.cpp, menuStuff.cpp
extern uint32_t        slotErrors;                        		//-- from DSMRlogger32
//-- used in DSMRsetupStuff.cpp, menuStuff.cpp
extern ESPSL           sysLog;                            		//-- from DSMRlogger32
//-- used in DSMRlogger32.cpp, restAPI.cpp, menuStuff.cpp, FSYSstuff.cpp, processTelegram.cpp, handleSlimmeMeter.cpp
extern uint32_t        telegramCount;                     		//-- from DSMRlogger32
//-- used in DSMRlogger32.cpp, restAPI.cpp, menuStuff.cpp, processTelegram.cpp, handleSlimmeMeter.cpp
extern uint32_t        telegramErrors;                    		//-- from DSMRlogger32
//-- used in FSYSstuff.cpp
extern uint32_t        telegramsAtStart;                  		//-- from DSMRlogger32
//-- used in handleTestdata.cpp, restAPI.cpp, FSYSstuff.cpp, processTelegram.cpp, helperStuff.cpp, handleSlimmeMeter.cpp
extern MyData          tlgrmData;                         		//-- from DSMRlogger32
//-- used in FSYSstuff.cpp
extern bool            tmpAlterRingSlots;                 		//-- from DSMRlogger32
//-- used in FSYSstuff.cpp
extern uint8_t         tmpNoDaySlots;                     		//-- from DSMRlogger32
//-- used in FSYSstuff.cpp
extern uint8_t         tmpNoHourSlots;                    		//-- from DSMRlogger32
//-- used in FSYSstuff.cpp
extern uint8_t         tmpNoMonthSlots;                   		//-- from DSMRlogger32
//-- used in helperStuff.cpp
extern uint64_t        upTimeSeconds;                     		//-- from DSMRlogger32
//-- used in helperStuff.cpp
extern uint64_t        upTimeStart;                       		//-- from DSMRlogger32
//-- used in DSMRlogger32.cpp
extern bool            updatedRINGfiles;                  		//-- from DSMRlogger32
//-- used in restAPI.cpp, FSYSstuff.cpp
extern char            buffer[100];                       		//-- from FSYSstuff
//-- used in FSYSstuff.cpp
extern int16_t         bytesRead;                         		//-- from FSYSstuff
//-- used in DSMRlogger32.cpp, FSYSstuff.cpp
extern char            key[10];                           		//-- from FSYSstuff
//-- used in FSYSstuff.cpp
extern timeStruct      newTime;                           		//-- from FSYSstuff
//-- used in FSYSstuff.cpp
extern uint16_t        recSlot;                           		//-- from FSYSstuff
//-- used in restAPI.cpp, processTelegram.cpp, FSYSstuff.cpp
extern char            record[];           		                //-- from FSYSstuff
//-- used in restAPI.cpp, processTelegram.cpp, FSYSstuff.cpp
extern char            record[];           		                //-- from FSYSstuff
//-- used in restAPI.cpp, FSYSstuff.cpp
extern char            fName[33];                         		//-- from FSmanager
//-- used in FSYSstuff.cpp
extern String          temp;                              		//-- from FSmanager
//-- used in restAPI.cpp, handleSlimmeMeter.cpp
extern char            crcChar[10];                       		//-- from handleSlimmeMeter
//-- used in handleTestdata.cpp
extern int8_t          State;                             		//-- from handleTestdata
//-- used in menuStuff.cpp
extern bool            forceBuildRingFiles;               		//-- from handleTestdata
//-- used in FSmanager.cpp, FSYSstuff.cpp, menuStuff.cpp
extern char            dummy[DATA_RECLEN];                		//-- from menuStuff
//-- used in handleTestdata.cpp, restAPI.cpp, networkStuff.cpp, DSMRlogger32.cpp
extern WebServer       httpServer;                        		//-- from networkStuff
//-- used in DSMRlogger32.cpp
extern SSD1306AsciiWire oled;                              		//-- from oledStuff
//-- used in restAPI.cpp, processTelegram.cpp, FSYSstuff.cpp
extern char            record[];           		                //-- from processTelegram
//-- used in settingsStuff.cpp, FSYSstuff.cpp
extern float           EDT1;                              		//-- from restAPI
//-- used in settingsStuff.cpp, FSYSstuff.cpp
extern float           EDT2;                              		//-- from restAPI
//-- used in settingsStuff.cpp, FSYSstuff.cpp
extern float           ERT1;                              		//-- from restAPI
//-- used in settingsStuff.cpp, FSYSstuff.cpp
extern float           ERT2;                              		//-- from restAPI
//-- used in settingsStuff.cpp, FSYSstuff.cpp
extern float           GDT;                               		//-- from restAPI gas delivered
extern float           WDT;                               		//-- from restAPI water delivered
//-- used in restAPI.cpp, FSYSstuff.cpp
extern char            buffer[];            		              //-- from restAPI
//-- used in restAPI.cpp, handleSlimmeMeter.cpp
extern char            crcChar[10];                       		//-- from restAPI
//-- used in settingsStuff.cpp
extern char            newValue[101];                     		//-- from restAPI
//-- used in DSMRlogger32.cpp
extern bool            firstConnectionLost;               		//-- from wifiEvents
//-- used in DSMRlogger32.cpp, helperStuff.cpp, networkStuff.cpp
extern bool            lostWiFiConnection;                		//-- from wifiEvents
//-- used in DSMRlogger32.cpp
extern int             lostWiFiCount;                     		//-- from wifiEvents

extern char                 *tlgrmTmpData;
extern char                 *tlgrmRaw;
extern char                 *jsonBuff;
extern char                 *gMsg;
extern char                 *fChar;

extern fieldTableStruct     *fieldTable; 
extern settingSmStruct      *smSetting;
extern settingDevStruct     *devSetting;
extern settingShieldStruct  *shieldSetting[2];
extern actualDataStruct     *actualStore;


//============ Function Prototypes =========
//-- from MQTTstuff.ino -----------
//-- Used in: DSMRlogger32.cpp, MQTTstuff.cpp
void connectMQTT();                                         
//-- Used in: MQTTstuff.cpp
bool connectMQTT_FSM();                                     
//-- Used in: processTelegram.cpp, MQTTstuff.cpp
void sendMQTTData();                                        
//-- from handleSlimmeMeter.ino -----------
//-- Used in: DSMRlogger32.cpp, handleSlimmeMeter.cpp
void handleSlimmemeter();                                   
//-- Used in: handleSlimmeMeter.cpp
void processSlimmemeterRaw();                               
//-- Used in: handleSlimmeMeter.cpp
void processSlimmemeter();                                  
//-- Used in: handleTestdata.cpp, handleSlimmeMeter.cpp
void modifySmFaseInfo();                                    
//-- Used in: handleTestdata.cpp, handleSlimmeMeter.cpp
float modifyMbusDelivered(int mbusType);                                

//-- from FSmanager.ino -----------
//-- Used in: FSmanager.cpp, DSMRlogger32.cpp
void setupFSmanager();                                      
//-- Used in: FSmanager.cpp, FSYSstuff.cpp
int sortFunction(const void *cmp1, const void *cmp2);       
//-- from oledStuff.ino -----------
//-- Used in: DSMRlogger32.cpp, oledStuff.cpp
void checkFlashButton();                                    
//-- Used in: DSMRlogger32.cpp, settingsStuff.cpp, oledStuff.cpp
void oled_Init();                                           
//-- Used in: DSMRlogger32.cpp, networkStuff.cpp, oledStuff.cpp
void oled_Clear();                                          
//-- Used in: DSMRlogger32.cpp, networkStuff.cpp, FSYSstuff.cpp, oledStuff.cpp, processTelegram.cpp, handleSlimmeMeter.cpp
void oled_Print_Msg(uint8_t line, String message, uint16_t wait);
//-- from processTelegram.ino -----------
//-- Used in: handleTestdata.cpp, processTelegram.cpp, handleSlimmeMeter.cpp
void processTelegram();                                     
//-- from settingsStuff.ino -----------
//-- Used in: DSMRlogger32.cpp, settingsStuff.cpp, menuStuff.cpp
void readSmSettings(bool show);                             
//-- Used in: settingsStuff.cpp, restAPI.cpp
void updateSmSettings(const char *field, const char *newValue);
//-- Used in: settingsStuff.cpp, FSYSstuff.cpp
void writeDevSettings(bool show);                           
void writeShieldSettings(bool show);                           
//-- Used in: DSMRlogger32.cpp, settingsStuff.cpp, menuStuff.cpp
void readDevSettings(bool show); 
void readShieldSettings(bool show); 
//-- Used in: settingsStuff.cpp, restAPI.cpp
void updateDevSettings(const char *field, const char *newValue);
void updateShieldSettings(const char *field, const char *newValue);

//-- from safeTimers.h -----------
uint32_t __Due__(uint32_t &timer_due, uint32_t timer_interval, byte timerType);
uint32_t __TimeLeft__(uint32_t timer_due);                  
uint32_t getParam(int i, ...);                              

#endif // ARDUINOGLUE_H
