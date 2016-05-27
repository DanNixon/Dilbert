#include "Dilbert.h"

Dilbert::Dilbert(size_t numNeoPixels) :
  m_tftDisplay(new Adafruit_ILI9341(TFT_CS_GPIO, TFT_DC_GPIO))
  , m_neopixels(new Adafruit_NeoPixel(numNeoPixels, NEOPIXEL_GPIO, NEO_GRB + NEO_KHZ800))
{
  // Init display
  m_tftDisplay->begin();
  m_tftDisplay->fillScreen(ILI9341_BLACK);
  setBacklightOn(true);

  // Init NeoPixels
  m_neopixels->begin();
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
