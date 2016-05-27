#include "Dilbert.h"

Dilbert::Dilbert() :
  m_tftDisplay(new Adafruit_ILI9341(TFT_CS_PIN, TFT_DC_PIN))
{
  // Init display
  m_tftDisplay->begin();
  m_tftDisplay->fillScreen(ILI9341_BLACK);
  setBacklightOn(true);
}

Dilbert::~Dilbert()
{
  delete m_tftDisplay;
}

/**
 * @brief Sets the backlight intensity.
 * @param on Boolean intensity
 */
void Dilbert::setBacklightOn(bool on)
{
  setBacklight(on ? 255 : 0);
}

/**
 * @brief Sets the backlight intensity.
 * @param intensity Intensity
 *
 * Where 0 is off and 255 is brightest.
 */
void Dilbert::setBacklight(uint8_t intensity)
{
  m_backlightIntensity = intensity;

  // TODO
}
