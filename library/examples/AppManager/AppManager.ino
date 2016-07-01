/* #include <GDBStub.h> */

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_ILI9341.h>

#include <Adafruit_MCP23017.h>
#include <Dilbert.h>
#include <DilbertAppManager.h>

#include "DemoApp.h"

/* #define USE_BUTTON_INTERRUPTS */

Dilbert badge;
DilbertAppManager appManager(&badge);

#ifdef USE_BUTTON_INTERRUPTS
volatile bool gpio_interrupt;
#endif

void setup()
{
  badge.begin();
  appManager.begin();

  appManager.addApp(new DemoApp("ONE"));
  appManager.addApp(new DemoApp("TWO"));
  appManager.addApp(new DemoApp("THREE"));

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
void handle_int()
{
  gpio_interrupt = true;
}
#endif
