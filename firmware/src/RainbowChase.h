/*! @file */

#ifndef _RAINBOW_CHASE_
#define _RAINBOW_CHASE_

#include "NPPattern.h"

class RainbowChase : public NPPattern
{
public:
  RainbowChase(Adafruit_NeoPixel &strip, uint8_t wait)
      : NPPattern(strip, 31)
      , m_wait(wait)
      , m_j(0)
      , m_q(0)
  {
    m_next = millis();
  }

  virtual ~RainbowChase()
  {
  }

  void run()
  {
    if (m_next < millis())
    {
      m_next = millis() + m_wait;
      if (m_j < 256)
      {
        if (m_q < 3)
        {
          for (uint16_t i = 0; i < m_strip.numPixels(); i += 3)
          {
            m_strip.setPixelColor(i + m_q, 0);
            m_strip.setPixelColor((i + m_q + 1) % m_strip.numPixels(), wheel((i + m_j) % 255));
          }
          m_strip.setBrightness(m_brightness);
          m_strip.show();
          m_q++;
        }
        else
        {
          m_q = 0;
        }
        if (m_q >= 3)
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
  int m_j, m_q;
};

#endif
