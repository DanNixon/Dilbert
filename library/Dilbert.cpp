/*! @file */

#include "Dilbert.h"

#include "MCP23017Button.h"

/**
 * @brief Create a new driver.
 */
Dilbert::Dilbert()
    : m_io(NULL)
    , m_tftDisplay(NULL)
    , m_buttons(NULL)
    , m_neopixels(NULL)
{
}

Dilbert::~Dilbert()
{
  if (m_io)
    delete m_io;
  if (m_tftDisplay)
    delete m_tftDisplay;
  if (m_buttons)
    delete m_buttons;
  if (m_neopixels)
    delete m_neopixels;
}

/**
 * @brief Initialises the badge hardware
 * @param numNeoPixels Number of neo pixels (defaults to 8)
 */
void Dilbert::begin(size_t numNeoPixels)
{
  ESP.wdtDisable();

  /* Init IO */
  m_io = new Adafruit_MCP23017();
  m_io->begin();
  m_io->setupInterrupts(true, false, LOW);
  pinMode(MCP23017_INT_GPIO, INPUT_PULLUP);

  /* Init display */
  m_tftDisplay = new Adafruit_ILI9341(TFT_CS_GPIO, TFT_DC_GPIO);
  m_tftDisplay->begin();
  m_tftDisplay->fillScreen(ILI9341_BLACK);

  /* Init backlight */
  pinMode(TFT_BACKLIGHT_GPIO, OUTPUT);
  setBacklightOn(false);

  /* Init buttons and add to manager */
  m_buttons = new UniversalInputManager();
  m_buttons->addDevice(new MCP23017Button(m_io, BUTTON_UP, BUTTON_UP));
  m_buttons->addDevice(new MCP23017Button(m_io, BUTTON_DOWN, BUTTON_DOWN));
  m_buttons->addDevice(new MCP23017Button(m_io, BUTTON_LEFT, BUTTON_LEFT));
  m_buttons->addDevice(new MCP23017Button(m_io, BUTTON_RIGHT, BUTTON_RIGHT));
  m_buttons->addDevice(new MCP23017Button(m_io, BUTTON_A, BUTTON_A));
  m_buttons->addDevice(new MCP23017Button(m_io, BUTTON_B, BUTTON_B));

  /* Init NeoPixels */
  m_neopixels = new Adafruit_NeoPixel(numNeoPixels, NEOPIXEL_GPIO, NEO_GRB + NEO_KHZ800);
  m_neopixels->begin();

  ESP.wdtEnable(5000);
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
