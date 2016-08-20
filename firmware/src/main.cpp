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
#include <UniversalInputManager.h>
#include <IButton.h>

#include <Adafruit_MCP23017.h>
#include <Dilbert.h>
#include <AppManager.h>
#include <MenuApp.h>
#include <SystemSettingsApp.h>
#include <SPIFFSConfigService.h>
#include <ConfigService.h>

#include "DebugApp.h"
#include "ProfileApp.h"
#include "StarsApp.h"
#include "DilbertApp.h"
#include "Conways.h"
#include "NeoTestApp.h"

/* #define USE_BUTTON_INTERRUPTS */

Dilbert badge;                 //!< Badge driver
AppManager appManager(&badge); //!< Badge application manager

#ifdef USE_BUTTON_INTERRUPTS
volatile bool gpio_interrupt;
#endif

void setup()
{
  badge.begin();

  /* Set storage */
  ConfigService::Instance().setStorage(new SPIFFSConfigService());

  badge.buttons().poll();
  IButton * bButton = (IButton *)badge.buttons().getDevice(Dilbert::BUTTON_B);

  /* Reset settings if B is held on startup */
  if (bButton->isActive())
  {
    ConfigService::Instance().save();
  }
  else
  {
    /* Load config or save the default values if it is not set */
    if(!ConfigService::Instance().load())
      ConfigService::Instance().save();
  }

  /* Add the app menu application
   * Typically this shoud always be the first added */
  appManager.addApp(new MenuApp(2));

  /* Add other applications */
  appManager.addApp(new SystemSettingsApp());
  appManager.addApp(new ProfileApp());
  appManager.addApp(new DebugApp());
  appManager.addApp(new StarsApp());
  appManager.addApp(new DilbertApp());
  appManager.addApp(new Conways());
  appManager.addApp(new NeoTestApp());

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
