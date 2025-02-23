#ifndef DEBUG_H
#define DEBUG_H

/*
***************************************************************************
**  Program  : Debug.h, part of DSMRlogger32
**  Version  : v2.0.1
**
**  Copyright (c) 2020 .. 2022 Willem Aandewiel
**  Met dank aan Erik
**
**  TERMS OF USE: MIT License. See bottom of file.
***************************************************************************
*/
//============ Includes ====================
#include "arduinoGlue.h"

char _bol[128];
void _debugBOL(const char *fn, int line)
{
  time(&now);
  struct tm  tstruct;
  localtime_r(&now, &tstruct);

  snprintf(_bol, sizeof(_bol), "[%02d:%02d:%02d] %-20.20s(%4d): ", tstruct.tm_hour, tstruct.tm_min, tstruct.tm_sec, fn, line);

  Serial.print (_bol);
  Serial.flush();       //esp32
  TelnetStream.print (_bol);
  TelnetStream.flush(); //esp32
}

#endif // DEBUG_H