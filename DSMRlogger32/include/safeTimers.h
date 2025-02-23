#pragma once

//#include <stdint.h>
//#include "Arduino.h
#include "arduinoGlue.h"

#define SKIP_MISSED_TICKS             0
#define SKIP_MISSED_TICKS_WITH_SYNC   1
#define CATCH_UP_MISSED_TICKS         2
#define DECLARE_TIMER_EXTERN(timerName, ...) \
    extern uint32_t timerName##_interval; \
    extern uint32_t timerName##_due; \
    extern byte timerName##_type;


#define DECLARE_TIMER_MIN(timerName, ...) \
  uint32_t timerName##_interval = (getParam(0, __VA_ARGS__, 0) * 60 * 1000), \
                                         timerName##_due  = millis() \
                                             +timerName##_interval \
                                             +random(timerName##_interval / 3); \
  byte     timerName##_type = getParam(1, __VA_ARGS__, 0);
#define DECLARE_TIMER_SEC(timerName, ...) \
  uint32_t timerName##_interval = (getParam(0, __VA_ARGS__, 0) * 1000), \
                                         timerName##_due  = millis() \
                                             +timerName##_interval \
                                             +random(timerName##_interval / 3); \
  byte     timerName##_type = getParam(1, __VA_ARGS__, 0);
#define DECLARE_TIMER_MS(timerName, ...) \
  uint32_t timerName##_interval = (getParam(0, __VA_ARGS__, 0)), \
                                         timerName##_due  = millis() \
                                             +timerName##_interval \
                                             +random(timerName##_interval / 3); \
  byte     timerName##_type = getParam(1, __VA_ARGS__, 0);
#define DECLARE_TIMER   DECLARE_TIMER_MS
#define CHANGE_INTERVAL_MIN(timerName, ...) \
  timerName##_interval = (getParam(0, __VA_ARGS__, 0) *60*1000); \
  timerName##_due  = millis() +timerName##_interval;
#define CHANGE_INTERVAL_SEC(timerName, ...) \
  timerName##_interval = (getParam(0, __VA_ARGS__, 0) *1000); \
  timerName##_due  = millis() +timerName##_interval;
#define CHANGE_INTERVAL_MS(timerName, ...) \
  timerName##_interval = (getParam(0, __VA_ARGS__, 0) ); \
  timerName##_due  = millis() +timerName##_interval;
#define CHANGE_INTERVAL CHANGE_INTERVAL_MS
#define TIME_LEFT(timerName)          ( __TimeLeft__(timerName##_due) )
#define TIME_LEFT_MS(timerName)       ( (TIME_LEFT(timerName) ) )
#define TIME_LEFT_MIN(timerName)      ( (TIME_LEFT(timerName) ) / (60 * 1000))
#define TIME_LEFT_SEC(timerName)      ( (TIME_LEFT(timerName) ) / 1000 )
#define TIME_PAST(timerName)          ( (timerName##_interval - TIME_LEFT(timerName)) )
#define TIME_PAST_MS(timerName)       ( (TIME_PAST(timerName) )
#define TIME_PAST_SEC(timerName)      ( (TIME_PAST(timerName) / 1000) )
#define TIME_PAST_MIN(timerName)      ( (TIME_PAST(timerName) / (60*1000)) )
#define RESTART_TIMER(timerName)      ( timerName##_due = millis()+timerName##_interval );
#define DUE(timerName)                ( __Due__(timerName##_due, timerName##_interval, timerName##_type) )

uint32_t __Due__(uint32_t &timer_due, uint32_t timer_interval, byte timerType);
uint32_t __TimeLeft__(uint32_t timer_due);
uint32_t getParam(int i, ...);
