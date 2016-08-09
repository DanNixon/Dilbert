/*! @file */

#ifndef _RAINBOW_CYCLE_
#define _RAINBOW_CYCLE_

#include "NPPattern.h"

class RainbowCycle : public NPPattern
{
  unsigned long wait, next;
  int j;

public:
  RainbowCycle(Adafruit_NeoPixel *inStrip, uint8_t inWait)
      : NPPattern(inStrip, 31)
      , wait(inWait)
      , j(0)
  {
    next = millis();
  }

  virtual ~RainbowCycle()
  {
  }

  void run()
  {
    if (next < millis())
    {
      next = millis() + wait;
      if (j < 256)
      {
        for (int i = 0; i < strip->numPixels(); i++)
        {
          strip->setPixelColor(i, wheel(((i * 256 / strip->numPixels()) + j) & 255));
        }
        strip->setBrightness(brightness);
        strip->show();
        j++;
      }
      else
      {
        j = 0;
      }
    }
  }
};

#endif
