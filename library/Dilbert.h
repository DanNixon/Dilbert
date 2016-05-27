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

  private:
    Adafruit_ILI9341 *m_tftDisplay;
};

#endif
