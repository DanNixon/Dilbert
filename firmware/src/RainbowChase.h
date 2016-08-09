/*! @file */

#ifndef _RAINBOW_CHASE_
#define _RAINBOW_CHASE_

#include "NPPattern.h"

class RainbowChase : public NPPattern
{
  unsigned long wait, next;
  int j, q;

public:
  RainbowChase(Adafruit_NeoPixel *inStrip, uint8_t inWait)
      : NPPattern(inStrip, 31)
      , wait(inWait)
      , j(0)
      , q(0)
  {
    next = millis();
  }

  virtual ~RainbowChase()
  {
  }

  void run()
  {
    if (next < millis())
    {
      next = millis() + wait;
      if (j < 256)
      {
        if (q < 3)
        {
          for (uint16_t i = 0; i < strip->numPixels(); i += 3)
          {
            strip->setPixelColor(i + q, 0);
            strip->setPixelColor((i + q + 1) % strip->numPixels(), wheel((i + j) % 255));
          }
          strip->setBrightness(brightness);
          strip->show();
          q++;
        }
        else
        {
          q = 0;
        }
        if (q >= 3)
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
