/* #include <GDBStub.h> */

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_ILI9341.h>
#include <IButton.h>

#include <Adafruit_MCP23017.h>
#include <Dilbert.h>

Dilbert *badge;

volatile bool gpio_interrupt;

void setup()
{
  badge = new Dilbert();

  badge->setBacklight(100);

  // Set NeoPixels
  badge->neoPixels().setBrightness(4);

  badge->neoPixels().setPixelColor(0, Adafruit_NeoPixel::Color(255, 0, 0));
  badge->neoPixels().show();
  badge->neoPixels().setPixelColor(1, Adafruit_NeoPixel::Color(0, 255, 0));
  badge->neoPixels().show();
  badge->neoPixels().setPixelColor(2, Adafruit_NeoPixel::Color(0, 0, 255));
  badge->neoPixels().show();
  badge->neoPixels().setPixelColor(3, Adafruit_NeoPixel::Color(120, 120, 120));
  badge->neoPixels().show();
  badge->neoPixels().setPixelColor(4, Adafruit_NeoPixel::Color(255, 0, 0));
  badge->neoPixels().show();
  badge->neoPixels().setPixelColor(5, Adafruit_NeoPixel::Color(0, 255, 0));
  badge->neoPixels().show();
  badge->neoPixels().setPixelColor(6, Adafruit_NeoPixel::Color(0, 0, 255));
  badge->neoPixels().show();
  badge->neoPixels().setPixelColor(7, Adafruit_NeoPixel::Color(120, 120, 120));
  badge->neoPixels().show();

  gpio_interrupt = false;
  attachInterrupt(Dilbert::MCP23017_INT_GPIO, handle_int, FALLING);
  badge->buttons().setCallback(handle_buttons);
}

void loop()
{
  // Display demo
  badge->display().setCursor(0, 0);

  badge->display().setTextColor(ILI9341_RED);
  badge->display().setTextSize(3);
  badge->display().println("Hello, world!");

  badge->display().println();

  badge->display().setTextColor(ILI9341_BLUE);
  badge->display().setTextSize(3);
  badge->display().println("My name is\nDilbert!");

  badge->display().setCursor(0, 150);

  badge->display().fillRect(0, 150, 240, 80, ILI9341_BLACK);

  badge->display().setTextColor(ILI9341_YELLOW);
  badge->display().setTextSize(2);
  badge->display().println(millis());
  badge->display().println();

  badge->setBacklight(100);

  // Output GPIO expander ports
  badge->display().println(badge->io().readGPIOAB(), BIN);
  if (gpio_interrupt)
  {
    badge->buttons().poll();
    gpio_interrupt = false;
  }

  // Wait a bit
  delay(1000);
}

void handle_int()
{
  gpio_interrupt = true;
  badge->setBacklight(500);
}

void handle_buttons(inputtype_t type, IInputDevice *device)
{
  if (type == UIT_BUTTON)
  {
    IButton *button = (IButton *)device;

    if (button->isActive())
    {
      badge->display().print("Button ");
      badge->display().print(button->getID());
      badge->display().println(" pressed");
    }
    else
    {
      badge->display().print("Button ");
      badge->display().print(button->getID());
      badge->display().print(" released\nafter ");
      badge->display().print(button->lastActiveDuration());
      badge->display().println("ms.");
    }
  }
}
