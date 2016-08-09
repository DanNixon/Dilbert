/*! @file */

#ifndef _NPPATTERN_
#define _NPPATTERN_

class NPPattern
{
public:
  NPPattern(Adafruit_NeoPixel &strip, int brightness)
      : m_strip(strip)
      , m_brightness(brightness)
  {
  }

  virtual ~NPPattern()
  {
  }

  virtual void run(){};

  // Input a value 0 to 255 to get a color value.
  // The colours are a transition r - g - b - back to r.
  uint32_t wheel(byte wheelPos)
  {
    wheelPos = 255 - wheelPos;
    if (wheelPos < 85)
    {
      return Adafruit_NeoPixel::Color(255 - wheelPos * 3, 0, wheelPos * 3);
    }
    if (wheelPos < 170)
    {
      wheelPos -= 85;
      return Adafruit_NeoPixel::Color(0, wheelPos * 3, 255 - wheelPos * 3);
    }
    wheelPos -= 170;
    return Adafruit_NeoPixel::Color(wheelPos * 3, 255 - wheelPos * 3, 0);
  }

  inline void setBrightness(int inBrightness)
  {
    m_strip.setBrightness(inBrightness);
    m_brightness = m_strip.getBrightness();
  }

  inline int getBrightness()
  {
    return m_brightness;
  }

protected:
  Adafruit_NeoPixel &m_strip;
  int m_brightness;
};

#endif
