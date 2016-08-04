/*!
 * @file
 * @author Dan Nixon
 * @brief Example with application manager. Intended to be used as the badge
 *        firmware.
 */

/* #include <GDBStub.h> */

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_ILI9341.h>

#include <Adafruit_MCP23017.h>
#include <Dilbert.h>
#include <AppManager.h>
#include <MenuApp.h>
#include <ButtonTestApp.h>
#include <SystemSettingsApp.h>

#include "ProfileApp.h"
#include "StarsApp.h"

/* #define USE_BUTTON_INTERRUPTS */

Dilbert badge;                 //!< Badge driver
AppManager appManager(&badge); //!< Badge application manager

#ifdef USE_BUTTON_INTERRUPTS
volatile bool gpio_interrupt;
#endif

void setup()
{
  badge.begin();

  /* Add the app menu application
   * Typically this shoud always be the first added */
  appManager.addApp(new MenuApp(2));

  /* Add other applications */
  appManager.addApp(new SystemSettingsApp());
  appManager.addApp(new ProfileApp());
  appManager.addApp(new ButtonTestApp());
  appManager.addApp(new StarsApp());

  /* Small delay before app manager start (which turns on backlight) */
  delay(100);

  /* Must call this after adding all apps */
  appManager.begin();

#ifdef USE_BUTTON_INTERRUPTS
  /* Button interrupt setup */
  gpio_interrupt = false;
  attachInterrupt(Dilbert::MCP23017_INT_GPIO, handle_int, FALLING);
#endif
}

void loop()
{
  appManager.run();

#ifdef USE_BUTTON_INTERRUPTS
  if (gpio_interrupt)
  {
    badge.buttons().poll();
    gpio_interrupt = false;
  }
#else
  badge.buttons().poll();
#endif
}

#ifdef USE_BUTTON_INTERRUPTS
/**
 * @brief Handle MCP23017 interrupt.
 */
void handle_int()
{
  gpio_interrupt = true;
}
#endif
