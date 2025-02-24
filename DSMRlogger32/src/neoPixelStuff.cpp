//============ Includes ====================
//#include "arduinoGlue.h"
#include <Adafruit_NeoPixel.h>
#include "neoPixelStuff.h"

const int _NEO_PIXELS_COUNT = 2;

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
void neoPixOn(int neoPixNr, NeoPixColor color)
{
  if (neoPixNr >= _NEO_PIXELS_COUNT) {
    return;
  }

  switch(color) {
    case NeoPixColor::red:
      neoPixels.setPixelColor(neoPixNr, neoPixels.Color(255, 0, 0));
      break;
    case NeoPixColor::greenLow:
      neoPixels.setPixelColor(neoPixNr, neoPixels.Color(0, 20, 0));
      break;
    case NeoPixColor::green:
      neoPixels.setPixelColor(neoPixNr, neoPixels.Color(0, 255, 0));
      break;
    case NeoPixColor::blue:
      neoPixels.setPixelColor(neoPixNr, neoPixels.Color(0, 0, 255));
      break;
    case NeoPixColor::whiteLow:
      neoPixels.setPixelColor(neoPixNr, neoPixels.Color(50, 50, 50));
      break;
    default:  //-- NeoPixColor::white
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
          neoPixOn(0, NeoPixColor::red);
          neoPixOff(1);
          break;
        case 2:
          neoPixOn(0, NeoPixColor::red);
          neoPixOn(1, NeoPixColor::red);
          break;
        case 3:
          neoPixOn(0, NeoPixColor::green);
          neoPixOn(1, NeoPixColor::red);
          break;
        case 4:
          neoPixOn(0, NeoPixColor::green);
          neoPixOn(1, NeoPixColor::green);
          break;
        case 5:
          neoPixOn(0, NeoPixColor::blue);
          neoPixOn(1, NeoPixColor::green);
          break;
        case 6:
          neoPixOn(0, NeoPixColor::blue);
          neoPixOn(1, NeoPixColor::blue);
          break;
        case 7:
          neoPixOn(0, NeoPixColor::white);
          neoPixOn(1, NeoPixColor::blue);
          break;
        case 8:
          neoPixOn(0, NeoPixColor::white);
          neoPixOn(1, NeoPixColor::white);
          break;
        case 9:
          neoPixOff(0);
          neoPixOn(1, NeoPixColor::white);
          break;
        case 10:
          neoPixOff(0);
          neoPixOff(1);
          break;
        default:
          neoPixOn(0, NeoPixColor::greenLow);
          neoPixOn(1, NeoPixColor::greenLow);
          break;

      } //  switch
      delay(speed/10);

    } // per step
  } // times
  neoPixOff(0);
  neoPixOff(1);
} //  blinkNeoPixels()
