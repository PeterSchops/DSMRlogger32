//============ Includes ====================
//#include "arduinoGlue.h"
#include <Adafruit_NeoPixel.h>
#include "neoPixelStuff.h"

Adafruit_NeoPixel neoPixels = Adafruit_NeoPixel(_NEO_PIXELS_COUNT, _NEO_PIN, NEO_GRB + NEO_KHZ800);

//----------------------------------------------------------------
void neoPixOff(int neoPixNr)
{
  if (neoPixNr >= _NEO_PIXELS_COUNT) {
    return;
  }
  neoPixels.setPixelColor(neoPixNr, neoPixels.Color(0, 0, 0));
  neoPixels.show();
} //  neoPixOff()

//----------------------------------------------------------------
void neoPixOn(int neoPixNr, neoPixColor color)
{
  if (neoPixNr >= _NEO_PIXELS_COUNT) {
    return;
  }

  switch(color) {
    case neoPixRed:
      neoPixels.setPixelColor(neoPixNr, neoPixels.Color(255, 0, 0));
      break;
    case neoPixGreenLow:
      neoPixels.setPixelColor(neoPixNr, neoPixels.Color(0, 20, 0));
      break;
    case neoPixGreen:
      neoPixels.setPixelColor(neoPixNr, neoPixels.Color(0, 255, 0));
      break;
    case neoPixBlue:
      neoPixels.setPixelColor(neoPixNr, neoPixels.Color(0, 0, 255));
      break;
    case neoPixWhiteLow:
      neoPixels.setPixelColor(neoPixNr, neoPixels.Color(50, 50, 50));
      break;
    default:  //-- neoPixWhite
      neoPixels.setPixelColor(neoPixNr, neoPixels.Color(255, 255, 255));
  }
  //-- Update neoPixels
  neoPixels.show();

} //  neoPixOn()

//===========================================================================================
void blinkNeoPixels(uint8_t times, uint16_t speed)
{
  if (times < 1) {
    times = 1;
  }
  if (speed < 100) {
    speed = 100;
  }

  for (int t=0; t<times; t++) {
    for(int c=0; c<=10; c++) {
      switch(c) {
        case 0:
          neoPixOff(0);
          neoPixOff(1);
          break;
        case 1:
          neoPixOn(0, neoPixRed);
          neoPixOff(1);
          break;
        case 2:
          neoPixOn(0, neoPixRed);
          neoPixOn(1, neoPixRed);
          break;
        case 3:
          neoPixOn(0, neoPixGreen);
          neoPixOn(1, neoPixRed);
          break;
        case 4:
          neoPixOn(0, neoPixGreen);
          neoPixOn(1, neoPixGreen);
          break;
        case 5:
          neoPixOn(0, neoPixBlue);
          neoPixOn(1, neoPixGreen);
          break;
        case 6:
          neoPixOn(0, neoPixBlue);
          neoPixOn(1, neoPixBlue);
          break;
        case 7:
          neoPixOn(0, neoPixWhite);
          neoPixOn(1, neoPixBlue);
          break;
        case 8:
          neoPixOn(0, neoPixWhite);
          neoPixOn(1, neoPixWhite);
          break;
        case 9:
          neoPixOff(0);
          neoPixOn(1, neoPixWhite);
          break;
        case 10:
          neoPixOff(0);
          neoPixOff(1);
          break;
        default:
          neoPixOn(0, neoPixGreenLow);
          neoPixOn(1, neoPixGreenLow);
          break;

      } //  switch
      delay(speed/10);

    } // per step
  } // times
  neoPixOff(0);
  neoPixOff(1);
} //  blinkNeoPixels()
