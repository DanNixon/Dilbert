#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include <Dilbert.h>

Dilbert *badge;

void setup()
{
  badge = new Dilbert();

  Serial.begin(9600);
  Serial.println("Display test");

  uint8_t x;

  x = badge->display().readcommand8(ILI9341_RDMODE);
  Serial.print("Display Power Mode: 0x");
  Serial.println(x, HEX);

  x = badge->display().readcommand8(ILI9341_RDMADCTL);
  Serial.print("MADCTL Mode: 0x");
  Serial.println(x, HEX);

  x = badge->display().readcommand8(ILI9341_RDPIXFMT);
  Serial.print("Pixel Format: 0x");
  Serial.println(x, HEX);

  x = badge->display().readcommand8(ILI9341_RDIMGFMT);
  Serial.print("Image Format: 0x");
  Serial.println(x, HEX);

  x = badge->display().readcommand8(ILI9341_RDSELFDIAG);
  Serial.print("Self Diagnostic: 0x");
  Serial.println(x, HEX);
}

void loop()
{
  badge->display().setCursor(0, 0);

  badge->display().setTextColor(ILI9341_RED);
  badge->display().setTextSize(3);
  badge->display().println("Hello, world!");

  badge->display().println();

  badge->display().setTextColor(ILI9341_BLUE);
  badge->display().setTextSize(3);
  badge->display().println("My name is\nDilbert!");

  badge->display().setCursor(0, 150);

  badge->display().fillRect(0, 150, 240, 20, ILI9341_BLACK);

  badge->display().setTextColor(ILI9341_YELLOW);
  badge->display().setTextSize(2);
  badge->display().println(millis());

  delay(1000);
}
