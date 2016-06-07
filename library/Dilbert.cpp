#include "Dilbert.h"

/**
 * @brief Create a new driver.
 * @param numNeoPixels NUmber of neo pixels (defaults to 8)
 */
Dilbert::Dilbert(size_t numNeoPixels)
    : m_io(new Adafruit_MCP23017())
    , m_tftDisplay(new Adafruit_ILI9341(TFT_CS_GPIO, TFT_DC_GPIO))
    , m_neopixels(new Adafruit_NeoPixel(numNeoPixels, NEOPIXEL_GPIO,
                                        NEO_GRB + NEO_KHZ800))
{
  ESP.wdtDisable();

  // Init IO
  m_io->begin();

  // Init display
  m_tftDisplay->begin();
  m_tftDisplay->fillScreen(ILI9341_BLACK);

  // Init backlight
  pinMode(TFT_BACKLIGHT_GPIO, OUTPUT);
  setBacklightOn(true);

  // Init NeoPixels
  m_neopixels->begin();

  ESP.wdtEnable(5000);
}

Dilbert::~Dilbert()
{
  delete m_io;
  delete m_tftDisplay;
  delete m_neopixels;
}

/**
 * @brief Sets the backlight intensity.
 * @param on Boolean intensity
 */
void Dilbert::setBacklightOn(bool on)
{
  setBacklight(on ? PWMRANGE : 0);
}

/**
 * @brief Sets the backlight intensity.
 * @param intensity Intensity
 *
 * Where 0 is off and 1023 is brightest.
 */
void Dilbert::setBacklight(uint16_t intensity)
{
  m_backlightIntensity = intensity;
  analogWrite(TFT_BACKLIGHT_GPIO, intensity);
}
