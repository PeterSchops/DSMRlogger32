#include "arduinoGlue.h"

void _debugBOL(const char *fn, int line)
{
  time_t now = time(NULL);
  time(&now);
  struct tm  tstruct;
  localtime_r(&now, &tstruct);

  char _bol[128];
  snprintf(_bol, sizeof(_bol), "[%02d:%02d:%02d] %-20.20s(%4d): ", tstruct.tm_hour, tstruct.tm_min, tstruct.tm_sec, fn, line);

  Serial.print (_bol);
  Serial.flush();       //esp32
  TelnetStream.print (_bol);
  TelnetStream.flush(); //esp32
}
