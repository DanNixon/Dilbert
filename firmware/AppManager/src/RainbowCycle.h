/*! @file */

#ifndef _RAINBOW_CYCLE_
#define _RAINBOW_CYCLE_

#include "NPPattern.h"

class RainbowCycle : public NPPattern
{
public:
  RainbowCycle(Adafruit_NeoPixel &strip, uint8_t wait)
      : NPPattern(strip, 31)
      , m_wait(wait)
      , m_j(0)
  {
    m_next = millis();
  }

  virtual ~RainbowCycle()
  {
  }

  void run()
  {
    if (m_next < millis())
    {
      m_next = millis() + m_wait;
      if (m_j < 256)
      {
        for (int i = 0; i < m_strip.numPixels(); i++)
        {
          m_strip.setPixelColor(i, wheel(((i * 256 / m_strip.numPixels()) + m_j) & 255));
        }
        m_strip.setBrightness(m_brightness);
        m_strip.show();
        m_j++;
      }
      else
      {
        m_j = 0;
      }
    }
  }

private:
  unsigned long m_wait, m_next;
  int m_j;
};

#endif
