#ifndef _DILBERT_H_
#define _DILBERT_H_

#include <Adafruit_NeoPixel.h>
#include <Adafruit_MCP23017.h>

#include <Adafruit_ILI9341.h>

/**
 * @class Dilbert
 * @author Dan Nixon
 * @brief Main hardware abstraction class.
 */
class Dilbert
{
public:
  static const uint8_t TFT_CS_GPIO = 4;
  static const uint8_t TFT_DC_GPIO = 2;
  static const uint8_t TFT_BACKLIGHT_GPIO = 16;
  static const uint8_t NEOPIXEL_GPIO = 15;

public:
  Dilbert(size_t numNeoPixels = 4);
  virtual ~Dilbert();

  /**
   * @brief Gets the TFT display driver.
   * @returns Reference to display driver
   */
  inline Adafruit_ILI9341 &display()
  {
    return *m_tftDisplay;
  }

  /**
   * @brief Gets the backlight intensity.
   * @return Intensity
   *
   * Where 0 is off and 1023 is brightest.
   */
  uint16_t backlight() const
  {
    return m_backlightIntensity;
  }

  void setBacklightOn(bool on);
  void setBacklight(uint16_t intensity);

  /**
   * @brief Gets the NeoPixel LED driver.
   * @return Reference to NeoPixel driver
   */
  inline Adafruit_NeoPixel &neoPixels()
  {
    return *m_neopixels;
  }

  /**
   * @brief Gets the IO expender driver.
   * @return Reference to the IO expander driver
   *
   * Warning: some of the IO pins are used for specific functions that are
   * managed elsewhere, do not set a pin that alreadyhas a function, this will
   * probably break something else.
   */
  inline Adafruit_MCP23017 &io()
  {
    return *m_io;
  }

private:
  Adafruit_MCP23017 *m_io;

  Adafruit_ILI9341 *m_tftDisplay;
  uint16_t m_backlightIntensity;

  Adafruit_NeoPixel *m_neopixels;
};

#endif
