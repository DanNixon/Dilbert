#ifndef _DILBERT_H_
#define _DILBERT_H_

#include <Adafruit_ILI9341.h>

/**
 * @class Dilbert
 * @author Dan Nixon
 * @brief Main hardware abstraction class.
 */
class Dilbert
{
  public:
    uint8_t TFT_CS_PIN = D2;
    uint8_t TFT_DC_PIN = D1;

  public:
    Dilbert();
    virtual ~Dilbert();

    /**
     * @brief Gets the TFT display driver.
     * @returns Reference to display driver
     */
    inline Adafruit_ILI9341 &display() const
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

  private:
    Adafruit_ILI9341 *m_tftDisplay;
    uint8_t m_backlightIntensity;
};

#endif
