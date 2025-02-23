#ifndef NEOPIXELSTUFF_H
#define NEOPIXELSTUFF_H

/*
***************************************************************************
**  Program  : neoPixelStuff, part of DSMRlogger32
**  Version  : v5.n
**
**  Copyright (c) 2020 .. 2023 Willem Aandewiel
**
**  TERMS OF USE: MIT License. See bottom of file.
***************************************************************************
*/
//============ Includes ====================
#include <Adafruit_NeoPixel.h>
#include "arduinoGlue.h"

//-- used in DSMRlogger32.cpp
extern Adafruit_NeoPixel neoPixels;               //-- from settingsStuff

//-- from neoPixelStuff.h
enum neoPixColor {
  neoPixWhiteLow,
  neoPixWhite,
  neoPixRed,
  neoPixGreenLow,
  neoPixGreen,
  neoPixBlue,
  neoPixFade,
  neoPixBlink,
};


//-- from neoPixelStuff.h -----------
//-- Used in: DSMRlogger32.cpp, networkStuff.cpp, FSYSstuff.cpp
void neoPixOff(int neoPixNr);                               
//-- Used in: handleTestdata.cpp, DSMRlogger32.cpp, networkStuff.cpp, FSYSstuff.cpp, helperStuff.cpp, handleSlimmeMeter.cpp
void neoPixOn(int neoPixNr, neoPixColor color);             
//-- Used in: DSMRlogger32.cpp, menuStuff.cpp
void blinkNeoPixels(uint8_t times, uint16_t speed);         




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
****************************************************************************
*/

#endif // NEOPIXELSTUFF_H