#ifndef _DILBERT_H_
#define _DILBERT_H_

#include <Adafruit_ILI9341.h>
#include <Adafruit_NeoPixel.h>

/**
 * @class Dilbert
 * @author Dan Nixon
 * @brief Main hardware abstraction class.
 */
class Dilbert
{
  public:
    uint8_t TFT_CS_GPIO = 4;
    uint8_t TFT_DC_GPIO = 5;
    uint8_t NEOPIXEL_GPIO = 15;

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
     * Where 0 is off and 255 is brightest.
     */
    uint8_t backlight() const
    {
      return m_backlightIntensity;
    }

    void setBacklightOn(bool on);
    void setBacklight(uint8_t intensity);

    /**
     * @brief Gets the NeoPixel LED driver.
     * @return Reference to NeoPixel driver
     */
    inline Adafruit_NeoPixel &neoPixels()
    {
      return *m_neopixels;
    }

  private:
    Adafruit_ILI9341 *m_tftDisplay;
    uint8_t m_backlightIntensity;

    Adafruit_NeoPixel *m_neopixels;
};

#endif
