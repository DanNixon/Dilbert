/*! @file */

#ifndef _DILBERT_H_
#define _DILBERT_H_

#include <Adafruit_ILI9341.h>
#include <Adafruit_NeoPixel.h>
#include <UniversalInputManager.h>

#include "Adafruit_MCP23017.h"

/**
 * @class Dilbert
 * @author Dan Nixon
 * @brief Main hardware abstraction class.
 */
class Dilbert
{
public:
  static const uint8_t MCP23017_INT_GPIO = 1;   //!< MCP23017 interrupt GPIO (on UART0 Tx)
  static const uint8_t SD_CS_GPIO = 3;          //!< SD chip select GPIO (on UART0 Rx)
  static const uint8_t TFT_CS_GPIO = 0;         //!< TFT chip select GPIO
  static const uint8_t TFT_DC_GPIO = 2;         //!< TFT DC GPIO
  static const uint8_t TFT_BACKLIGHT_GPIO = 16; //!< TFT backlight GPIO
  static const uint8_t NEOPIXEL_GPIO = 15;      //!< NeoPIxel GPIO

  static const uint8_t BUTTON_UP = 1;    //!< Up buppion GPIO (on MCP23017)
  static const uint8_t BUTTON_DOWN = 2;  //!< Down button GPIO (on MCP23017)
  static const uint8_t BUTTON_LEFT = 0;  //!< Left button GPIO (on MCP23017)
  static const uint8_t BUTTON_RIGHT = 3; //!< Right button GPIO (on MCP23017)
  static const uint8_t BUTTON_A = 4;     //!< A button GPIO (on MCP23017)
  static const uint8_t BUTTON_B = 5;     //!< B button GPIO (on MCP23017)

public:
  Dilbert();
  virtual ~Dilbert();

  void begin(size_t numNeoPixels = 8);

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

  /**
   * @brief Gets the button manager.
   * @return Reference to the button manager
   */
  inline UniversalInputManager &buttons()
  {
    return *m_buttons;
  }

private:
  Adafruit_MCP23017 *m_io; //!< IO expander driver

  Adafruit_ILI9341 *m_tftDisplay; //<! Display driver
  uint16_t m_backlightIntensity;  //!< Backlight intensity (0-1023)

  UniversalInputManager *m_buttons; //!< Button manager

  Adafruit_NeoPixel *m_neopixels; //!< NeoPixel driver
};

#endif
