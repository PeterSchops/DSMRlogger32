#ifndef DSMRLOGGER32_H
#define DSMRLOGGER32_H

/*
***************************************************************************
**  Program  : DSMRlogger32.h - definitions for DSMRlogger32
**  Version  : v5.n
**
**  Copyright (c) 2021, 2023 Willem Aandewiel
**
**  TERMS OF USE: MIT License. See bottom of file.
***************************************************************************
*/
//============ Includes ====================
#include "oledStuff.h"
#include "FSmanager.h"
#include "handleSlimmeMeter.h"
#include "FSYSstuff.h"
#include "networkStuff.h"
#include "processTelegram.h"
#include "DSMRsetupStuff.h"
#include "menuStuff.h"
#include "settingsStuff.h"
#include "MQTTstuff.h"
#include "restAPI.h"
#include "timeStuff.h"
#include "helperStuff.h"
#include "wifiEvents.h"
#include "Shield32.h"
#include "safeTimers.h"
#include "arduinoGlue.h"

//--- sanaty check ---
#if !defined(_LITTLEFS) && !defined(_SPIFFS)
  #error "We need one of these: LITTLEFS or SPIFFS !"
#endif
#if defined(_LITTLEFS) && defined(_SPIFFS)
  #error "Only one of these: LITTLEFS or SPIFFS can be used!"
#endif

#include "safeTimers.h"

//------ [Adafruit_NeoPixel@1.10.6]
#include "neoPixelStuff.h"
#include "Debug.h"
#include "wifiEvents.h"   // part of ESP32 Core https://github.com/ESP32/Arduino


/************** MOVED TO arduinoGlue.h ******************************************
 * Define the tlgrmData we're interested in, as well as the tlgrmDatastructure to
 * hold the parsed tlgrmData. This list shows all supported fields, remove
 * any fields you are not using from the below list to make the parsing
 * and printing code smaller.
 * Each template argument below results in a field of the same name.
 */


const char *TzLocation = "Europe/Amsterdam";

const char *flashMode[] { "QIO", "QOUT", "DIO", "DOUT", "Unknown" };



//=============== PROTOTYPES ====================================
void doSystemTasks();                                       




char actualTableArray[][35] = { "timestamp",
                          "power_delivered_l1", "power_delivered_l2", "power_delivered_l3",
                          "power_returned_l1", "power_returned_l2", "power_returned_l3",
                          "gas_delivered", "water_delivered", "\0"
                         };

int  actualTableElements = (sizeof(actualTableArray)/sizeof(actualTableArray[0]))-1;

char actualArray[][35] = { "timestamp",
                           "energy_delivered_tariff1", "energy_delivered_tariff2",
                           "energy_returned_tariff1", "energy_returned_tariff2",
                           "power_delivered", "power_returned",
                           "voltage_l1", "voltage_l2", "voltage_l3",
                           "current_l1", "current_l2", "current_l3",
                           "power_delivered_l1", "power_delivered_l2", "power_delivered_l3",
                           "power_returned_l1", "power_returned_l2", "power_returned_l3",
                           "mbus1_delivered",
                           "mbus2_delivered",
                           "mbus3_delivered",
                           "mbus4_delivered",
                           "relay_state",
                           "\0"
                         };

int  actualElements = (sizeof(actualArray)/sizeof(actualArray[0]))-1;

char infoArray[][35]   = { "identification", "p1_version", "p1_version_be",
                           "equipment_id",
                           "electricity_tariff",
                           "mbus1_device_type", "mbus1_equipment",
                           "mbus2_device_type", "mbus2_equipment",
                           "mbus3_device_type", "mbus3_equipment",
                           "mbus4_device_type", "mbus4_equipment",
                           "\0"
                         };

int  infoElements = (sizeof(infoArray)/sizeof(infoArray[0]))-1;

bool onlyIfPresent  = false;


char      lastResetCPU0[100]    = {0};
char      lastResetCPU1[100]    = {0};
bool      runAPmode             = false;
bool      filesysMounted        = false;
bool      filesysNotPopulated   = false;
bool      hasAlternativeIndex   = false;
bool      mqttIsConnected       = false;
bool      doLog = false, Verbose1 = false, Verbose2 = false;
int8_t    thisHour = -1, prevNtpHour = 0, thisDay = -1, thisMonth = -1, lastMonth, thisYear = 15;
uint32_t  unixTimestamp;
uint8_t   ntpEventId = 0;
uint64_t  upTimeStart, upTimeSeconds;
uint32_t  actualStoreCount = 0;
uint16_t  actualStoreSlot  = 0;

bool      skipHeartbeats = false;

bool      buttonState = LOW;
uint8_t   msgMode = 0;
bool      boolDisplay = true;
//-in wifiEvents.h - bool      lostWiFiConnection = true;

String    pTimestamp;
uint16_t  lastResetCount = 0;
uint32_t  glowTimer0, glowTimer1;

//===========================================================================================
// setup timers
DECLARE_TIMER_SEC(updateDisplay,       5);
DECLARE_TIMER_MIN(updateTlgrmCount, 4560);  //-- every 6 hours
DECLARE_TIMER_MIN(reconnectWiFi,      30);
DECLARE_TIMER_SEC(nextTelegram,       10);
DECLARE_TIMER_MIN(reconnectMQTTtimer,  2);  //-- try reconnecting cyclus timer
DECLARE_TIMER_SEC(publishMQTTtimer,   60, SKIP_MISSED_TICKS); // interval time between MQTT messages
DECLARE_TIMER_SEC(antiWearTimer,     301);
DECLARE_TIMER_MIN(oledSleepTimer,     10);  //-- sleep the display in 10 minutes
DECLARE_TIMER_SEC(shieldTimer,  _SHIELD_TIME);  //-- process shieldTask every _SHIELD_TIME seconds

/***************************************************************************
*
* Permission is hereby granted, free of charge, to any person obtaining a
* copy of this software and associated documentation files (the
* "Software"), to deal in the Software without restriction, including
* without limitation the rights to use, copy, modify, merge, publish,
* distribute, sublicense, and/or sell copies of the Software, and to permit
* persons to whom the Software is furnished to do so, subject to the
* following conditions:
*
* The above copyright notice and this permission notice shall be included
* in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
* OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
* OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR
* THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*
***************************************************************************/

#endif // DSMRLOGGER32_H